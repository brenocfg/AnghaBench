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
 int c2b (int /*<<< orphan*/ ) ; 
 unsigned char c64tobin (int /*<<< orphan*/ ) ; 
 char* malloc (int) ; 
 int strlen (char*) ; 
 scalar_t__ strncasecmp (char*,char*,int) ; 

int
str2bin(char *str, char **rsp)
{
     char	*src, *dst, *tmp;
     int	i, len = 0;

     src = str;
     tmp = NULL;
     if(strncasecmp("0x", src, 2) == 0) {
	  src += 2;
	  len = strlen(src);
	  
	  if((tmp = malloc((len+1)/2)) == NULL) {
	       // XXX: print some error?
	       return 0;
	  }
	  dst = tmp;
	  if(len & 1)
	       *dst++ = c2b(*src++);
	  while(*src) {
	       *dst = c2b(*src++) << 4;
	       *dst++ |= c2b(*src++);
	  }
	  len = dst - tmp;
     } else
     if(strncasecmp("0b", src , 2) == 0) {
	  // base64
	  unsigned char b6;

	  src += 2;
	  len = strlen(src) / 4 * 3;
	  if((tmp = malloc(len)) == NULL) {
	       // XXX: print some error?
	       return 0;
	  }
	  dst = tmp; 
	  i = 0;
	  while(*src && ((b6 = c64tobin(*src++)) != 64)) {
	       switch(i % 4) {
	       case 0:
		    *dst = b6 << 2;
		    break;
	       case 1:
		    *dst++ |= b6 >> 4;
		    *dst = b6 << 4;
		    break;
	       case 2:
		    *dst++ |= b6 >> 2;
		    *dst = b6 << 6;
		    break;
	       case 3:
		    *dst++ |= b6;
		    break;
	       }
	       i++;
	  }
	  len = dst - tmp;
     }
     else {
	  /*
	   | assume it to be an ascii string, so just copy it
	   */
	  len = strlen(str);
	  if((tmp = malloc(len)) == NULL)
	       return 0;
	  dst = tmp;
	  src = str;
	  while(*src)
	       *dst++ = *src++;
     }

     *rsp = tmp;
     return len;
}