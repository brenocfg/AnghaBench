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
struct client {int dummy; } ;
typedef  int int32_t ;

/* Variables and functions */
 int eAcquireCreds ; 
 int /*<<< orphan*/  put32 (struct client*,int) ; 
 int /*<<< orphan*/  putstring (struct client*,char const*) ; 
 int /*<<< orphan*/  ret32 (struct client*,int) ; 

__attribute__((used)) static int
acquire_cred(struct client *client,
	     const char *username,
	     const char *password,
	     int32_t flags,
	     int32_t *hCred)
{
    int32_t val;
    put32(client, eAcquireCreds);
    putstring(client, username);
    putstring(client, password);
    put32(client, flags);
    ret32(client, val);
    ret32(client, *hCred);
    return val;
}