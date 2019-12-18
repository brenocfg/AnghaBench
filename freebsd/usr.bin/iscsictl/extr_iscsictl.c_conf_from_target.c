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
struct target {scalar_t__ t_session_type; scalar_t__ t_enable; scalar_t__ t_protocol; scalar_t__ t_header_digest; scalar_t__ t_data_digest; int /*<<< orphan*/ * t_offload; int /*<<< orphan*/ * t_mutual_secret; int /*<<< orphan*/ * t_mutual_user; int /*<<< orphan*/ * t_secret; int /*<<< orphan*/ * t_user; int /*<<< orphan*/ * t_address; int /*<<< orphan*/ * t_name; int /*<<< orphan*/ * t_initiator_alias; int /*<<< orphan*/ * t_initiator_address; int /*<<< orphan*/ * t_initiator_name; } ;
struct iscsi_session_conf {int isc_discovery; int isc_enable; int isc_iser; void* isc_data_digest; void* isc_header_digest; int /*<<< orphan*/  isc_offload; int /*<<< orphan*/  isc_mutual_secret; int /*<<< orphan*/  isc_mutual_user; int /*<<< orphan*/  isc_secret; int /*<<< orphan*/  isc_user; int /*<<< orphan*/  isc_target_addr; int /*<<< orphan*/  isc_target; int /*<<< orphan*/  isc_initiator_alias; int /*<<< orphan*/  isc_initiator_addr; int /*<<< orphan*/  isc_initiator; } ;

/* Variables and functions */
 scalar_t__ DIGEST_CRC32C ; 
 scalar_t__ ENABLE_OFF ; 
 void* ISCSI_DIGEST_CRC32C ; 
 void* ISCSI_DIGEST_NONE ; 
 scalar_t__ PROTOCOL_ISER ; 
 scalar_t__ SESSION_TYPE_DISCOVERY ; 
 int /*<<< orphan*/  memset (struct iscsi_session_conf*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
conf_from_target(struct iscsi_session_conf *conf,
    const struct target *targ)
{
	memset(conf, 0, sizeof(*conf));

	/*
	 * XXX: Check bounds and return error instead of silently truncating.
	 */
	if (targ->t_initiator_name != NULL)
		strlcpy(conf->isc_initiator, targ->t_initiator_name,
		    sizeof(conf->isc_initiator));
	if (targ->t_initiator_address != NULL)
		strlcpy(conf->isc_initiator_addr, targ->t_initiator_address,
		    sizeof(conf->isc_initiator_addr));
	if (targ->t_initiator_alias != NULL)
		strlcpy(conf->isc_initiator_alias, targ->t_initiator_alias,
		    sizeof(conf->isc_initiator_alias));
	if (targ->t_name != NULL)
		strlcpy(conf->isc_target, targ->t_name,
		    sizeof(conf->isc_target));
	if (targ->t_address != NULL)
		strlcpy(conf->isc_target_addr, targ->t_address,
		    sizeof(conf->isc_target_addr));
	if (targ->t_user != NULL)
		strlcpy(conf->isc_user, targ->t_user,
		    sizeof(conf->isc_user));
	if (targ->t_secret != NULL)
		strlcpy(conf->isc_secret, targ->t_secret,
		    sizeof(conf->isc_secret));
	if (targ->t_mutual_user != NULL)
		strlcpy(conf->isc_mutual_user, targ->t_mutual_user,
		    sizeof(conf->isc_mutual_user));
	if (targ->t_mutual_secret != NULL)
		strlcpy(conf->isc_mutual_secret, targ->t_mutual_secret,
		    sizeof(conf->isc_mutual_secret));
	if (targ->t_session_type == SESSION_TYPE_DISCOVERY)
		conf->isc_discovery = 1;
	if (targ->t_enable != ENABLE_OFF)
		conf->isc_enable = 1;
	if (targ->t_protocol == PROTOCOL_ISER)
		conf->isc_iser = 1;
	if (targ->t_offload != NULL)
		strlcpy(conf->isc_offload, targ->t_offload,
		    sizeof(conf->isc_offload));
	if (targ->t_header_digest == DIGEST_CRC32C)
		conf->isc_header_digest = ISCSI_DIGEST_CRC32C;
	else
		conf->isc_header_digest = ISCSI_DIGEST_NONE;
	if (targ->t_data_digest == DIGEST_CRC32C)
		conf->isc_data_digest = ISCSI_DIGEST_CRC32C;
	else
		conf->isc_data_digest = ISCSI_DIGEST_NONE;
}