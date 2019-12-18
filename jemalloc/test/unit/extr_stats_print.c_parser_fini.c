#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * buf; } ;
typedef  TYPE_1__ parser_t ;

/* Variables and functions */
 int /*<<< orphan*/  MALLOCX_TCACHE_NONE ; 
 int /*<<< orphan*/  dallocx (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
parser_fini(parser_t *parser) {
	if (parser->buf != NULL) {
		dallocx(parser->buf, MALLOCX_TCACHE_NONE);
	}
}