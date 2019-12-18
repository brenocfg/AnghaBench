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
 int /*<<< orphan*/  LibAliasSetSkinnyPort (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  mla ; 
 int sscanf (char const*,char*,unsigned int*) ; 

__attribute__((used)) static void
SetupSkinnyPort(const char *strValue)
{
	unsigned int port;

	if (sscanf(strValue, "%u", &port) != 1)
		errx(1, "skinny_port: port parameter required");

	LibAliasSetSkinnyPort(mla, port);
}