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
struct zwp_primary_selection_offer_v1 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  O_CLOEXEC ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ pipe2 (int*,int /*<<< orphan*/ ) ; 
 char* read_offer_string (int) ; 
 int /*<<< orphan*/  zwp_primary_selection_offer_v1_receive (struct zwp_primary_selection_offer_v1*,char const*,int) ; 

__attribute__((used)) static char* read_primary_selection_offer(struct zwp_primary_selection_offer_v1 *primary_selection_offer, const char *mime) {
    int pipefd[2];
    if (pipe2(pipefd, O_CLOEXEC) != 0) return NULL;
    zwp_primary_selection_offer_v1_receive(primary_selection_offer, mime, pipefd[1]);
    close(pipefd[1]);
    return read_offer_string(pipefd[0]);
}