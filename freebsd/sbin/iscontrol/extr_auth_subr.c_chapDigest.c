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
 char* bin2str (char*,unsigned char*,int) ; 
 scalar_t__ chapMD5 (char,char*,char*,unsigned char*) ; 
 scalar_t__ chapSHA1 (char,char*,char*,unsigned char*) ; 
 int /*<<< orphan*/  debug_called (int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 scalar_t__ strcmp (char*,char*) ; 

char *
chapDigest(char *ap, char id, char *cp, char *chapSecret)
{
     int	len;
     unsigned	char digest[20];
     char	encoding[3];

     debug_called(3);

     len = 0;
     if(strcmp(ap, "5") == 0 && chapMD5(id, cp, chapSecret, digest) == 0)
	  len = 16;
     else
     if(strcmp(ap, "7") == 0 && chapSHA1(id, cp, chapSecret, digest) == 0)
	  len = 20;

     if(len) {
	  sprintf(encoding, "%.2s", cp);
	  return bin2str(encoding, digest, len);
     }

     return NULL;
}