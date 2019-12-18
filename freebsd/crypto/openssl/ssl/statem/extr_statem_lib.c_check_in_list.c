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
typedef  scalar_t__ uint16_t ;
typedef  int /*<<< orphan*/  SSL ;

/* Variables and functions */
 int /*<<< orphan*/  SSL_SECOP_CURVE_CHECK ; 
 scalar_t__ tls_curve_allowed (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 

int check_in_list(SSL *s, uint16_t group_id, const uint16_t *groups,
                  size_t num_groups, int checkallow)
{
    size_t i;

    if (groups == NULL || num_groups == 0)
        return 0;

    for (i = 0; i < num_groups; i++) {
        uint16_t group = groups[i];

        if (group_id == group
                && (!checkallow
                    || tls_curve_allowed(s, group, SSL_SECOP_CURVE_CHECK))) {
            return 1;
        }
    }

    return 0;
}