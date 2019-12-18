#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ abd_offset; } ;
struct TYPE_7__ {TYPE_1__ abd_scatter; } ;
struct TYPE_8__ {scalar_t__ abd_size; TYPE_2__ abd_u; } ;
typedef  TYPE_3__ abd_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 size_t abd_chunkcnt_for_bytes (scalar_t__) ; 
 int /*<<< orphan*/  abd_is_linear (TYPE_3__*) ; 

__attribute__((used)) static inline size_t
abd_scatter_chunkcnt(abd_t *abd)
{
	ASSERT(!abd_is_linear(abd));
	return (abd_chunkcnt_for_bytes(
	    abd->abd_u.abd_scatter.abd_offset + abd->abd_size));
}