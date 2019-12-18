#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  prog20; } ;
struct vsie_page {TYPE_1__ scb_s; } ;

/* Variables and functions */
 int PROG_REQUEST ; 
 int atomic_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int prefix_is_mapped(struct vsie_page *vsie_page)
{
	return !(atomic_read(&vsie_page->scb_s.prog20) & PROG_REQUEST);
}