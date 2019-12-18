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

/* Variables and functions */
 int /*<<< orphan*/  wrtmessage (int /*<<< orphan*/ *,char const*) ; 

void
wrtmessage_1_0(const char *s1, const char *s2, const char *s3, const char *s4) {

	wrtmessage(NULL, s1);
	wrtmessage(NULL, s2);
	wrtmessage(NULL, s3);
	wrtmessage(NULL, s4);
}