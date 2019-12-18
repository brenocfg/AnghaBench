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
struct sockaddr_s {int dummy; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_port; } ;

/* Variables and functions */
 int ntohs (int /*<<< orphan*/ ) ; 

int WINS_GetSocketPort( struct sockaddr_s *addr ){
	return ntohs( ( (struct sockaddr_in *)addr )->sin_port );
}