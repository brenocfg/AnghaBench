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
struct rsn_pmksa_cache_entry {char* spa; char* identity; int identity_len; int /*<<< orphan*/  cui; scalar_t__ acct_multi_session_id; } ;
struct radius_das_attrs {int acct_multi_session_id_len; int cui_len; int user_name_len; scalar_t__ user_name; scalar_t__ cui; scalar_t__ acct_multi_session_id; scalar_t__ sta_addr; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int ETH_ALEN ; 
 scalar_t__ os_memcmp (scalar_t__,char*,int) ; 
 int /*<<< orphan*/  os_snprintf (char*,int,char*,unsigned long long) ; 
 char* wpabuf_head (int /*<<< orphan*/ ) ; 
 int wpabuf_len (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int das_attr_match(struct rsn_pmksa_cache_entry *entry,
			  struct radius_das_attrs *attr)
{
	int match = 0;

	if (attr->sta_addr) {
		if (os_memcmp(attr->sta_addr, entry->spa, ETH_ALEN) != 0)
			return 0;
		match++;
	}

	if (attr->acct_multi_session_id) {
		char buf[20];

		if (attr->acct_multi_session_id_len != 16)
			return 0;
		os_snprintf(buf, sizeof(buf), "%016llX",
			    (unsigned long long) entry->acct_multi_session_id);
		if (os_memcmp(attr->acct_multi_session_id, buf, 16) != 0)
			return 0;
		match++;
	}

	if (attr->cui) {
		if (!entry->cui ||
		    attr->cui_len != wpabuf_len(entry->cui) ||
		    os_memcmp(attr->cui, wpabuf_head(entry->cui),
			      attr->cui_len) != 0)
			return 0;
		match++;
	}

	if (attr->user_name) {
		if (!entry->identity ||
		    attr->user_name_len != entry->identity_len ||
		    os_memcmp(attr->user_name, entry->identity,
			      attr->user_name_len) != 0)
			return 0;
		match++;
	}

	return match;
}