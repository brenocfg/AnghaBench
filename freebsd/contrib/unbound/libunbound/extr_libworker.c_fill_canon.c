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
struct ub_result {int /*<<< orphan*/  canonname; } ;

/* Variables and functions */
 int /*<<< orphan*/  dname_str (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  strdup (char*) ; 

__attribute__((used)) static int
fill_canon(struct ub_result* res, uint8_t* s)
{
	char buf[255+2];
	dname_str(s, buf);
	res->canonname = strdup(buf);
	return res->canonname != 0;
}