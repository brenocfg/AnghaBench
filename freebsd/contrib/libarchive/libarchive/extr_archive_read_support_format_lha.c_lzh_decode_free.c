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
struct lzh_stream {TYPE_1__* ds; } ;
struct TYPE_2__ {int /*<<< orphan*/  pt; int /*<<< orphan*/  lt; struct TYPE_2__* w_buff; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  lzh_huffman_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
lzh_decode_free(struct lzh_stream *strm)
{

	if (strm->ds == NULL)
		return;
	free(strm->ds->w_buff);
	lzh_huffman_free(&(strm->ds->lt));
	lzh_huffman_free(&(strm->ds->pt));
	free(strm->ds);
	strm->ds = NULL;
}