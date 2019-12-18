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

/* Variables and functions */
 int get_socket_priv (int) ; 
 int get_socket_unpriv (int) ; 

__attribute__((used)) static int
get_socket(int type, int priv)
{

	if (priv)
		return (get_socket_priv(type));
	else
		return (get_socket_unpriv(type));
}