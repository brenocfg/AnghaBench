#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {void* ptr; } ;
struct TYPE_4__ {TYPE_1__ mem; } ;
struct chunk {scalar_t__ ch_block; scalar_t__ ch_size; TYPE_2__ ch_u; int /*<<< orphan*/  ch_type; } ;
typedef  scalar_t__ lba_t ;

/* Variables and functions */
 int /*<<< orphan*/  CH_TYPE_MEMORY ; 
 int /*<<< orphan*/  TAILQ_INSERT_AFTER (int /*<<< orphan*/ *,struct chunk*,struct chunk*,int /*<<< orphan*/ ) ; 
 void* calloc (int,scalar_t__) ; 
 int /*<<< orphan*/  ch_list ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  image_chunks ; 
 int /*<<< orphan*/  image_nchunks ; 
 struct chunk* malloc (int) ; 
 int /*<<< orphan*/  memcpy (struct chunk*,struct chunk*,int) ; 
 scalar_t__ secsz ; 

__attribute__((used)) static struct chunk *
image_chunk_memory(struct chunk *ch, lba_t blk)
{
	struct chunk *new;
	void *ptr;

	ptr = calloc(1, secsz);
	if (ptr == NULL)
		return (NULL);

	if (ch->ch_block < blk) {
		new = malloc(sizeof(*new));
		if (new == NULL) {
			free(ptr);
			return (NULL);
		}
		memcpy(new, ch, sizeof(*new));
		ch->ch_size = (blk - ch->ch_block) * secsz;
		new->ch_block = blk;
		new->ch_size -= ch->ch_size;
		TAILQ_INSERT_AFTER(&image_chunks, ch, new, ch_list);
		image_nchunks++;
		ch = new;
	}

	if (ch->ch_size > secsz) {
		new = malloc(sizeof(*new));
		if (new == NULL) {
			free(ptr);
			return (NULL);
		}
		memcpy(new, ch, sizeof(*new));
		ch->ch_size = secsz;
		new->ch_block++;
		new->ch_size -= secsz;
		TAILQ_INSERT_AFTER(&image_chunks, ch, new, ch_list);
		image_nchunks++;
	}

	ch->ch_type = CH_TYPE_MEMORY;
	ch->ch_u.mem.ptr = ptr;
	return (ch);
}