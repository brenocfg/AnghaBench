#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct sysctl_oid {int dummy; } ;
struct nlm_host {int nh_refs; int nh_sysid; int nh_grantcookie; int /*<<< orphan*/  nh_sysctl; scalar_t__ nh_monstate; scalar_t__ nh_vers; int /*<<< orphan*/  nh_caller_name; int /*<<< orphan*/  nh_sysid_string; int /*<<< orphan*/  nh_finished; int /*<<< orphan*/  nh_granted; int /*<<< orphan*/  nh_pending; scalar_t__ nh_state; int /*<<< orphan*/  nh_lock; } ;

/* Variables and functions */
 int CTLFLAG_RD ; 
 int CTLTYPE_INT ; 
 int /*<<< orphan*/  MAXNAMELEN ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  M_NLM ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  NLM_DEBUG (int,char*,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ NLM_UNMONITORED ; 
 int /*<<< orphan*/  OID_AUTO ; 
 struct sysctl_oid* SYSCTL_ADD_NODE (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_PROC (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,struct nlm_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_STRING (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_UINT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,scalar_t__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SYSCTL_CHILDREN (struct sysctl_oid*) ; 
 int /*<<< orphan*/  SYSCTL_STATIC_CHILDREN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct nlm_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _vfs_nlm_sysid ; 
 struct nlm_host* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nh_link ; 
 int /*<<< orphan*/  nlm_global_lock ; 
 int /*<<< orphan*/  nlm_host_client_lock_count_sysctl ; 
 int /*<<< orphan*/  nlm_host_lock_count_sysctl ; 
 int /*<<< orphan*/  nlm_hosts ; 
 int /*<<< orphan*/  nlm_next_sysid ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysctl_ctx_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct nlm_host *
nlm_create_host(const char* caller_name)
{
	struct nlm_host *host;
	struct sysctl_oid *oid;

	mtx_assert(&nlm_global_lock, MA_OWNED);

	NLM_DEBUG(1, "NLM: new host %s (sysid %d)\n",
	    caller_name, nlm_next_sysid);
	host = malloc(sizeof(struct nlm_host), M_NLM, M_NOWAIT|M_ZERO);
	if (!host)
		return (NULL);
	mtx_init(&host->nh_lock, "nh_lock", NULL, MTX_DEF);
	host->nh_refs = 1;
	strlcpy(host->nh_caller_name, caller_name, MAXNAMELEN);
	host->nh_sysid = nlm_next_sysid++;
	snprintf(host->nh_sysid_string, sizeof(host->nh_sysid_string),
		"%d", host->nh_sysid);
	host->nh_vers = 0;
	host->nh_state = 0;
	host->nh_monstate = NLM_UNMONITORED;
	host->nh_grantcookie = 1;
	TAILQ_INIT(&host->nh_pending);
	TAILQ_INIT(&host->nh_granted);
	TAILQ_INIT(&host->nh_finished);
	TAILQ_INSERT_TAIL(&nlm_hosts, host, nh_link);

	mtx_unlock(&nlm_global_lock);

	sysctl_ctx_init(&host->nh_sysctl);
	oid = SYSCTL_ADD_NODE(&host->nh_sysctl,
	    SYSCTL_STATIC_CHILDREN(_vfs_nlm_sysid),
	    OID_AUTO, host->nh_sysid_string, CTLFLAG_RD, NULL, "");
	SYSCTL_ADD_STRING(&host->nh_sysctl, SYSCTL_CHILDREN(oid), OID_AUTO,
	    "hostname", CTLFLAG_RD, host->nh_caller_name, 0, "");
	SYSCTL_ADD_UINT(&host->nh_sysctl, SYSCTL_CHILDREN(oid), OID_AUTO,
	    "version", CTLFLAG_RD, &host->nh_vers, 0, "");
	SYSCTL_ADD_UINT(&host->nh_sysctl, SYSCTL_CHILDREN(oid), OID_AUTO,
	    "monitored", CTLFLAG_RD, &host->nh_monstate, 0, "");
	SYSCTL_ADD_PROC(&host->nh_sysctl, SYSCTL_CHILDREN(oid), OID_AUTO,
	    "lock_count", CTLTYPE_INT | CTLFLAG_RD, host, 0,
	    nlm_host_lock_count_sysctl, "I", "");
	SYSCTL_ADD_PROC(&host->nh_sysctl, SYSCTL_CHILDREN(oid), OID_AUTO,
	    "client_lock_count", CTLTYPE_INT | CTLFLAG_RD, host, 0,
	    nlm_host_client_lock_count_sysctl, "I", "");

	mtx_lock(&nlm_global_lock);

	return (host);
}