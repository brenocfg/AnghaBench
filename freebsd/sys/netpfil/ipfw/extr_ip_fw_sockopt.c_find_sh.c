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
typedef  int /*<<< orphan*/  uint16_t ;
struct ipfw_sopt_handler {int /*<<< orphan*/ * handler; int /*<<< orphan*/  version; int /*<<< orphan*/  opcode; } ;
typedef  int /*<<< orphan*/  sopt_handler_f ;
typedef  int /*<<< orphan*/  h ;

/* Variables and functions */
 scalar_t__ bsearch (struct ipfw_sopt_handler*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  compare_sh ; 
 int /*<<< orphan*/  ctl3_handlers ; 
 int /*<<< orphan*/  ctl3_hsize ; 
 int /*<<< orphan*/  memset (struct ipfw_sopt_handler*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct ipfw_sopt_handler *
find_sh(uint16_t code, uint8_t version, sopt_handler_f *handler)
{
	struct ipfw_sopt_handler *sh, h;

	memset(&h, 0, sizeof(h));
	h.opcode = code;
	h.version = version;
	h.handler = handler;

	sh = (struct ipfw_sopt_handler *)bsearch(&h, ctl3_handlers,
	    ctl3_hsize, sizeof(h), compare_sh);

	return (sh);
}