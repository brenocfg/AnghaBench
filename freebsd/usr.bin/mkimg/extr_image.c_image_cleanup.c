#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct chunk* ptr; } ;
struct TYPE_4__ {int fd; } ;
struct TYPE_6__ {TYPE_2__ mem; TYPE_1__ file; } ;
struct chunk {int ch_type; TYPE_3__ ch_u; } ;

/* Variables and functions */
#define  CH_TYPE_FILE 129 
#define  CH_TYPE_MEMORY 128 
 struct chunk* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct chunk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ch_list ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  free (struct chunk*) ; 
 int /*<<< orphan*/  image_chunks ; 
 int image_swap_fd ; 
 int /*<<< orphan*/  image_swap_file ; 
 int /*<<< orphan*/  unlink (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
image_cleanup(void)
{
	struct chunk *ch;

	while ((ch = TAILQ_FIRST(&image_chunks)) != NULL) {
		switch (ch->ch_type) {
		case CH_TYPE_FILE:
			/* We may be closing the same file multiple times. */
			if (ch->ch_u.file.fd != -1)
				close(ch->ch_u.file.fd);
			break;
		case CH_TYPE_MEMORY:
			free(ch->ch_u.mem.ptr);
			break;
		default:
			break;
		}
		TAILQ_REMOVE(&image_chunks, ch, ch_list);
		free(ch);
	}
	if (image_swap_fd != -1)
		close(image_swap_fd);
	unlink(image_swap_file);
}