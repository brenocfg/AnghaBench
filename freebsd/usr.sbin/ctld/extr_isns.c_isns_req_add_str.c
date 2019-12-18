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
typedef  int /*<<< orphan*/  uint32_t ;
struct isns_req {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  isns_req_add (struct isns_req*,int /*<<< orphan*/ ,scalar_t__,char const*) ; 
 scalar_t__ strlen (char const*) ; 

void
isns_req_add_str(struct isns_req *req, uint32_t tag, const char *value)
{

	isns_req_add(req, tag, strlen(value) + 1, value);
}