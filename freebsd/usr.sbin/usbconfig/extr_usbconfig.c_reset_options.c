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
struct options {scalar_t__ buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (scalar_t__) ; 
 int /*<<< orphan*/  memset (struct options*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
reset_options(struct options *opt)
{
	if (opt->buffer)
		free(opt->buffer);
	memset(opt, 0, sizeof(*opt));
	return;
}