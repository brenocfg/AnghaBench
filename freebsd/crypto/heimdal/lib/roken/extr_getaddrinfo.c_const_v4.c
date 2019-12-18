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
struct in_addr {int dummy; } ;
struct sockaddr_in {int sin_port; struct in_addr sin_addr; int /*<<< orphan*/  sin_family; } ;
struct addrinfo {int ai_addrlen; int /*<<< orphan*/ * ai_addr; int /*<<< orphan*/  ai_family; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int EAI_MEMORY ; 
 int /*<<< orphan*/  PF_INET ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int /*<<< orphan*/  memset (struct sockaddr_in*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
const_v4 (struct addrinfo *a, void *data, int port)
{
    struct sockaddr_in *sin4;
    struct in_addr *addr = (struct in_addr *)data;

    a->ai_family  = PF_INET;
    a->ai_addrlen = sizeof(*sin4);
    a->ai_addr    = malloc (sizeof(*sin4));
    if (a->ai_addr == NULL)
	return EAI_MEMORY;
    sin4 = (struct sockaddr_in *)a->ai_addr;
    memset (sin4, 0, sizeof(*sin4));
    sin4->sin_family = AF_INET;
    sin4->sin_port   = port;
    sin4->sin_addr   = *addr;
    return 0;
}