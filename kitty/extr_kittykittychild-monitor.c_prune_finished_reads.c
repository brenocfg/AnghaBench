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
struct TYPE_7__ {int num_reads; TYPE_1__* reads; } ;
struct TYPE_6__ {int /*<<< orphan*/  data; int /*<<< orphan*/  fd; scalar_t__ close_socket; scalar_t__ finished; } ;
typedef  TYPE_1__ PeerReadData ;

/* Variables and functions */
 int /*<<< orphan*/  SHUT_RD ; 
 TYPE_1__ empty_prd ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (TYPE_1__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  nuke_socket (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_poll_fd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shutdown (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__ talk_data ; 

__attribute__((used)) static inline void
prune_finished_reads() {
    if (!talk_data.num_reads) return;
    for (ssize_t i = talk_data.num_reads - 1; i >= 0; i--) {
        PeerReadData *rd = talk_data.reads + i;
        if (rd->finished) {
            remove_poll_fd(rd->fd);
            if (rd->close_socket) { nuke_socket(rd->fd); }
            else shutdown(rd->fd, SHUT_RD);
            free(rd->data);
            ssize_t num_to_right = talk_data.num_reads - 1 - i;
            if (num_to_right > 0) memmove(talk_data.reads + i, talk_data.reads + i + 1, num_to_right * sizeof(PeerReadData));
            else talk_data.reads[i] = empty_prd;
            talk_data.num_reads--;
        }
    }
}