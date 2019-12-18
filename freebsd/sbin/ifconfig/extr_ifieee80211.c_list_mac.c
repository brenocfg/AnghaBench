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
typedef  int /*<<< orphan*/  uint8_t ;
struct ieee80211req_maclist {scalar_t__ ml_macaddr; } ;
struct ieee80211req {int i_val; int i_len; int /*<<< orphan*/ * i_data; int /*<<< orphan*/  i_type; int /*<<< orphan*/  i_name; } ;
struct ether_addr {int dummy; } ;
typedef  int /*<<< orphan*/  ireq ;

/* Variables and functions */
 scalar_t__ EINVAL ; 
 int /*<<< orphan*/  IEEE80211_IOC_MACCMD ; 
 int IEEE80211_MACCMD_LIST ; 
 int IEEE80211_MACCMD_POLICY ; 
 int IEEE80211_MACCMD_POLICY_ALLOW ; 
 int IEEE80211_MACCMD_POLICY_DENY ; 
 int IEEE80211_MACCMD_POLICY_OPEN ; 
 int IEEE80211_MACCMD_POLICY_RADIUS ; 
 int /*<<< orphan*/  SIOCG80211 ; 
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  ether_ntoa (struct ether_addr const*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,struct ieee80211req*) ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int /*<<< orphan*/  memset (struct ieee80211req*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  name ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  printpolicy (int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ verbose ; 

__attribute__((used)) static void
list_mac(int s)
{
	struct ieee80211req ireq;
	struct ieee80211req_maclist *acllist;
	int i, nacls, policy, len;
	uint8_t *data;
	char c;

	(void) memset(&ireq, 0, sizeof(ireq));
	(void) strlcpy(ireq.i_name, name, sizeof(ireq.i_name)); /* XXX ?? */
	ireq.i_type = IEEE80211_IOC_MACCMD;
	ireq.i_val = IEEE80211_MACCMD_POLICY;
	if (ioctl(s, SIOCG80211, &ireq) < 0) {
		if (errno == EINVAL) {
			printf("No acl policy loaded\n");
			return;
		}
		err(1, "unable to get mac policy");
	}
	policy = ireq.i_val;
	if (policy == IEEE80211_MACCMD_POLICY_OPEN) {
		c = '*';
	} else if (policy == IEEE80211_MACCMD_POLICY_ALLOW) {
		c = '+';
	} else if (policy == IEEE80211_MACCMD_POLICY_DENY) {
		c = '-';
	} else if (policy == IEEE80211_MACCMD_POLICY_RADIUS) {
		c = 'r';		/* NB: should never have entries */
	} else {
		printf("policy: unknown (%u)\n", policy);
		c = '?';
	}
	if (verbose || c == '?')
		printpolicy(policy);

	ireq.i_val = IEEE80211_MACCMD_LIST;
	ireq.i_len = 0;
	if (ioctl(s, SIOCG80211, &ireq) < 0)
		err(1, "unable to get mac acl list size");
	if (ireq.i_len == 0) {		/* NB: no acls */
		if (!(verbose || c == '?'))
			printpolicy(policy);
		return;
	}
	len = ireq.i_len;

	data = malloc(len);
	if (data == NULL)
		err(1, "out of memory for acl list");

	ireq.i_data = data;
	if (ioctl(s, SIOCG80211, &ireq) < 0)
		err(1, "unable to get mac acl list");
	nacls = len / sizeof(*acllist);
	acllist = (struct ieee80211req_maclist *) data;
	for (i = 0; i < nacls; i++)
		printf("%c%s\n", c, ether_ntoa(
			(const struct ether_addr *) acllist[i].ml_macaddr));
	free(data);
}