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
struct wl_data_offer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  O_CLOEXEC ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ pipe2 (int*,int /*<<< orphan*/ ) ; 
 char* read_offer_string (int) ; 
 int /*<<< orphan*/  wl_data_offer_receive (struct wl_data_offer*,char const*,int) ; 

__attribute__((used)) static char* read_data_offer(struct wl_data_offer *data_offer, const char *mime) {
    int pipefd[2];
    if (pipe2(pipefd, O_CLOEXEC) != 0) return NULL;
    wl_data_offer_receive(data_offer, mime, pipefd[1]);
    close(pipefd[1]);
    return read_offer_string(pipefd[0]);
}