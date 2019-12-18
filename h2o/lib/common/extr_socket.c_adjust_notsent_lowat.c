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
typedef  int /*<<< orphan*/  notsent_lowat ;
typedef  int /*<<< orphan*/  h2o_socket_t ;

/* Variables and functions */
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int /*<<< orphan*/  TCP_NOTSENT_LOWAT ; 
 int /*<<< orphan*/  h2o_socket_get_fd (int /*<<< orphan*/ *) ; 
 int setsockopt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*,int) ; 

__attribute__((used)) static int adjust_notsent_lowat(h2o_socket_t *sock, unsigned notsent_lowat)
{
    return setsockopt(h2o_socket_get_fd(sock), IPPROTO_TCP, TCP_NOTSENT_LOWAT, &notsent_lowat, sizeof(notsent_lowat));
}