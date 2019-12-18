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
struct local_zones {int dummy; } ;
typedef  int /*<<< orphan*/  RES ;

/* Variables and functions */
 int /*<<< orphan*/  perform_data_add (int /*<<< orphan*/ *,struct local_zones*,char*) ; 
 int /*<<< orphan*/  send_ok (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
do_data_add(RES* ssl, struct local_zones* zones, char* arg)
{
	if(!perform_data_add(ssl, zones, arg))
		return;
	send_ok(ssl);
}