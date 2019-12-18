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
struct ieee802_1x_mka_sci {int dummy; } ;
typedef  int Boolean ;

/* Variables and functions */
 scalar_t__ os_memcmp (struct ieee802_1x_mka_sci const*,struct ieee802_1x_mka_sci const*,int) ; 

__attribute__((used)) static Boolean sci_equal(const struct ieee802_1x_mka_sci *a,
			 const struct ieee802_1x_mka_sci *b)
{
	return os_memcmp(a, b, sizeof(struct ieee802_1x_mka_sci)) == 0;
}