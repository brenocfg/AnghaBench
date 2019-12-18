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
struct TYPE_3__ {int /*<<< orphan*/  trailers; int /*<<< orphan*/  _trailer_block; } ;
typedef  TYPE_1__ git_message_trailer_array ;

/* Variables and functions */
 int /*<<< orphan*/  git__free (int /*<<< orphan*/ ) ; 

void git_message_trailer_array_free(git_message_trailer_array *arr)
{
	git__free(arr->_trailer_block);
	git__free(arr->trailers);
}