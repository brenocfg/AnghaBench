#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ name; } ;
typedef  TYPE_1__ textkey_t ;

/* Variables and functions */
 TYPE_1__* keyMap ; 
 scalar_t__ strcasecmp (char*,scalar_t__) ; 
 scalar_t__ strcmp (scalar_t__,char*) ; 

__attribute__((used)) static textkey_t *
keyLookup(char *key)
{
     textkey_t	*tk;

     for(tk = keyMap; tk->name && strcmp(tk->name, "end"); tk++) {
	  if(strcasecmp(key, tk->name) == 0)
	       return tk;
     }
     return NULL;
}