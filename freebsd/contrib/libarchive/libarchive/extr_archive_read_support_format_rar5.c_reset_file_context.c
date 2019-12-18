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
struct TYPE_6__ {scalar_t__ redir_flags; int /*<<< orphan*/  redir_type; int /*<<< orphan*/  b2state; } ;
struct TYPE_5__ {scalar_t__ last_unstore_ptr; scalar_t__ last_write_ptr; scalar_t__ write_ptr; scalar_t__ solid_offset; } ;
struct TYPE_4__ {scalar_t__ solid; } ;
struct rar5 {TYPE_3__ file; TYPE_2__ cstate; TYPE_1__ main; } ;

/* Variables and functions */
 int /*<<< orphan*/  REDIR_TYPE_NONE ; 
 int /*<<< orphan*/  blake2sp_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  free_filters (struct rar5*) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void reset_file_context(struct rar5* rar) {
	memset(&rar->file, 0, sizeof(rar->file));
	blake2sp_init(&rar->file.b2state, 32);

	if(rar->main.solid) {
		rar->cstate.solid_offset += rar->cstate.write_ptr;
	} else {
		rar->cstate.solid_offset = 0;
	}

	rar->cstate.write_ptr = 0;
	rar->cstate.last_write_ptr = 0;
	rar->cstate.last_unstore_ptr = 0;

	rar->file.redir_type = REDIR_TYPE_NONE;
	rar->file.redir_flags = 0;

	free_filters(rar);
}