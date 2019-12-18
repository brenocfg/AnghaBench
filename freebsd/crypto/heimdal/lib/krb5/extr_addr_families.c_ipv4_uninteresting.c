#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ s_addr; } ;
struct sockaddr_in {TYPE_1__ sin_addr; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  krb5_boolean ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ INADDR_ANY ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static krb5_boolean
ipv4_uninteresting (const struct sockaddr *sa)
{
    const struct sockaddr_in *sin4 = (const struct sockaddr_in *)sa;

    if (sin4->sin_addr.s_addr == INADDR_ANY)
	return TRUE;

    return FALSE;
}