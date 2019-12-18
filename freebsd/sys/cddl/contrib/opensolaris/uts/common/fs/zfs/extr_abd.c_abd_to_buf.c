#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {void* abd_buf; } ;
struct TYPE_8__ {TYPE_1__ abd_linear; } ;
struct TYPE_9__ {TYPE_2__ abd_u; } ;
typedef  TYPE_3__ abd_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  abd_is_linear (TYPE_3__*) ; 
 int /*<<< orphan*/  abd_verify (TYPE_3__*) ; 

void *
abd_to_buf(abd_t *abd)
{
	ASSERT(abd_is_linear(abd));
	abd_verify(abd);
	return (abd->abd_u.abd_linear.abd_buf);
}