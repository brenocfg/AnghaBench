#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int ssize_t ;
struct TYPE_7__ {int num_writes; TYPE_1__* writes; } ;
struct TYPE_6__ {int /*<<< orphan*/  data; int /*<<< orphan*/  fd; scalar_t__ finished; } ;
typedef  TYPE_1__ PeerWriteData ;

/* Variables and functions */
 int /*<<< orphan*/  SHUT_WR ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 TYPE_1__ empty_pwd ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (TYPE_1__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  remove_poll_fd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shutdown (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__ talk_data ; 

__attribute__((used)) static inline void
prune_finished_writes() {
    if (!talk_data.num_writes) return;
    for (ssize_t i = talk_data.num_writes - 1; i >= 0; i--) {
        PeerWriteData *wd = talk_data.writes + i;
        if (wd->finished) {
            remove_poll_fd(wd->fd);
            shutdown(wd->fd, SHUT_WR); close(wd->fd);
            free(wd->data);
            ssize_t num_to_right = talk_data.num_writes - 1 - i;
            if (num_to_right > 0) memmove(talk_data.writes + i, talk_data.writes + i + 1, num_to_right * sizeof(PeerWriteData));
            else talk_data.writes[i] = empty_pwd;
            talk_data.num_writes--;
        }
    }
}