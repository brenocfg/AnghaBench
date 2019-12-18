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
struct ucl_emitter_functions {int* ud; int /*<<< orphan*/  (* ucl_emitter_free_func ) (struct ucl_emitter_functions*) ;int /*<<< orphan*/  ucl_emitter_append_len; int /*<<< orphan*/  ucl_emitter_append_int; int /*<<< orphan*/  ucl_emitter_append_double; int /*<<< orphan*/  ucl_emitter_append_character; } ;
typedef  int /*<<< orphan*/  fd ;

/* Variables and functions */
 struct ucl_emitter_functions* calloc (int,int) ; 
 int /*<<< orphan*/  free (struct ucl_emitter_functions*) ; 
 int* malloc (int) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  ucl_fd_append_character ; 
 int /*<<< orphan*/  ucl_fd_append_double ; 
 int /*<<< orphan*/  ucl_fd_append_int ; 
 int /*<<< orphan*/  ucl_fd_append_len ; 

struct ucl_emitter_functions*
ucl_object_emit_fd_funcs (int fd)
{
	struct ucl_emitter_functions *f;
	int *ip;

	f = calloc (1, sizeof (*f));

	if (f != NULL) {
		ip = malloc (sizeof (fd));
		if (ip == NULL) {
			free (f);
			return NULL;
		}

		memcpy (ip, &fd, sizeof (fd));
		f->ucl_emitter_append_character = ucl_fd_append_character;
		f->ucl_emitter_append_double = ucl_fd_append_double;
		f->ucl_emitter_append_int = ucl_fd_append_int;
		f->ucl_emitter_append_len = ucl_fd_append_len;
		f->ucl_emitter_free_func = free;
		f->ud = ip;
	}

	return f;
}