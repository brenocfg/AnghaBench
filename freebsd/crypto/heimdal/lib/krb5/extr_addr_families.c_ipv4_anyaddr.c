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
typedef  int /*<<< orphan*/  tmp ;
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {int sin_port; TYPE_1__ sin_addr; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int dummy; } ;
typedef  int krb5_socklen_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  INADDR_ANY ; 
 int /*<<< orphan*/  memcpy (struct sockaddr*,struct sockaddr_in*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct sockaddr_in*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  min (int,int) ; 

__attribute__((used)) static void
ipv4_anyaddr (struct sockaddr *sa, krb5_socklen_t *sa_size, int port)
{
    struct sockaddr_in tmp;

    memset (&tmp, 0, sizeof(tmp));
    tmp.sin_family = AF_INET;
    tmp.sin_port   = port;
    tmp.sin_addr.s_addr = INADDR_ANY;
    memcpy(sa, &tmp, min(sizeof(tmp), *sa_size));
    *sa_size = sizeof(tmp);
}