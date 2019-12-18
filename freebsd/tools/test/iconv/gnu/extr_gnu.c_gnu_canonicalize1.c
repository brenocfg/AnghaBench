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
 int /*<<< orphan*/  iconv_canonicalize (char*) ; 
 int strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
gnu_canonicalize1(void)
{

	return (strcmp(iconv_canonicalize("latin2"), "ISO-8859-2"));
}