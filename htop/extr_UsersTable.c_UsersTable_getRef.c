#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct passwd {int /*<<< orphan*/  pw_name; } ;
struct TYPE_3__ {int /*<<< orphan*/  users; } ;
typedef  TYPE_1__ UsersTable ;

/* Variables and functions */
 scalar_t__ Hashtable_get (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  Hashtable_put (int /*<<< orphan*/ ,unsigned int,char*) ; 
 struct passwd* getpwuid (unsigned int) ; 
 char* xStrdup (int /*<<< orphan*/ ) ; 

char* UsersTable_getRef(UsersTable* this, unsigned int uid) {
   char* name = (char*) (Hashtable_get(this->users, uid));
   if (name == NULL) {
      struct passwd* userData = getpwuid(uid);
      if (userData != NULL) {
         name = xStrdup(userData->pw_name);
         Hashtable_put(this->users, uid, name);
      }
   }
   return name;
}