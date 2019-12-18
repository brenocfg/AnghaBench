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
typedef  int /*<<< orphan*/  u8 ;
struct wpabuf {int dummy; } ;
struct wpa_cred {unsigned int num_roaming_consortiums; int /*<<< orphan*/ * roaming_consortiums_len; int /*<<< orphan*/ * roaming_consortiums; } ;

/* Variables and functions */
 scalar_t__ roaming_consortium_match (int /*<<< orphan*/  const*,struct wpabuf const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cred_roaming_consortiums_match(const u8 *ie,
					  const struct wpabuf *anqp,
					  const struct wpa_cred *cred)
{
	unsigned int i;

	for (i = 0; i < cred->num_roaming_consortiums; i++) {
		if (roaming_consortium_match(ie, anqp,
					     cred->roaming_consortiums[i],
					     cred->roaming_consortiums_len[i]))
			return 1;
	}

	return 0;
}