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
struct connection {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  custom; } ;

/* Variables and functions */
 int /*<<< orphan*/  SHA1 (unsigned char*,int,unsigned char*) ; 
 TYPE_1__* SQLS_DATA (struct connection*) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mrand48 () ; 
 scalar_t__ sql_password ; 
 int /*<<< orphan*/  sql_username ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 
 int strlen (scalar_t__) ; 

int sqlp_password (struct connection *c, const char *user, char buffer[20]) {
  memset (buffer, 0, 20);

  if (!strcmp (user, sql_username)) {
    unsigned char buffer2[20];
    SHA1 ((unsigned char *)sql_password, strlen (sql_password), buffer2);
    SHA1 (buffer2, 20, (unsigned char *)buffer);
    SQLS_DATA(c)->custom = mrand48();
    return 1;
  }
  
  return 0;
}