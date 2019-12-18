#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  line; TYPE_1__* pushback; int /*<<< orphan*/  at_eof; } ;
typedef  TYPE_2__ inputsource ;
struct TYPE_4__ {scalar_t__ current; } ;

/* Variables and functions */
 int EOF ; 
 int /*<<< orphan*/  ISC_FALSE ; 
 int /*<<< orphan*/  REQUIRE (int) ; 

__attribute__((used)) static void
pushback(inputsource *source, int c) {
	REQUIRE(source->pushback->current > 0);
	if (c == EOF) {
		source->at_eof = ISC_FALSE;
		return;
	}
	source->pushback->current--;
	if (c == '\n')
		source->line--;
}