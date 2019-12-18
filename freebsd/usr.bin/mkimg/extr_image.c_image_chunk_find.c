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
struct chunk {scalar_t__ ch_block; int ch_size; } ;
typedef  scalar_t__ lba_t ;

/* Variables and functions */
 struct chunk* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 struct chunk* TAILQ_NEXT (struct chunk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ch_list ; 
 int /*<<< orphan*/  image_chunks ; 
 int secsz ; 

__attribute__((used)) static struct chunk *
image_chunk_find(lba_t blk)
{
	static struct chunk *last = NULL;
	struct chunk *ch;

	ch = (last != NULL && last->ch_block <= blk)
	    ? last : TAILQ_FIRST(&image_chunks);
	while (ch != NULL) {
		if (ch->ch_block <= blk &&
		    (lba_t)(ch->ch_block + (ch->ch_size / secsz)) > blk) {
			last = ch;
			break;
		}
		ch = TAILQ_NEXT(ch, ch_list);
	}
	return (ch);
}