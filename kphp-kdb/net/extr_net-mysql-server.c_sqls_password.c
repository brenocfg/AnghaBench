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
struct connection {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SHA1 (unsigned char*,int,unsigned char*) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

int sqls_password (struct connection *c, const char *user, char buffer[20]) {
  memset (buffer, 0, 20);

  if (!strcmp (user, "kitten")) {
    unsigned char buffer2[20];
    SHA1 ((unsigned char *)"test", 4, buffer2);
    SHA1 (buffer2, 20, (unsigned char *)buffer);
    return 2;
  }
  
  return 1;
}