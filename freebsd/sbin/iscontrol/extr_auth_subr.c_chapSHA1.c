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
typedef  int /*<<< orphan*/  SHA1_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  SHA1_Final (unsigned char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SHA1_Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SHA1_Update (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  debug_called (int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int str2bin (char*,char**) ; 

__attribute__((used)) static int
chapSHA1(char id, char *cp, char *chapSecret, unsigned char *digest)
{
     SHA1_CTX	ctx;
     char	*tmp;
     int	len;

     debug_called(3);

     SHA1_Init(&ctx);
     
     SHA1_Update(&ctx, &id, 1);

     if((len = str2bin(chapSecret, &tmp)) == 0) {
	  // print error
	  return -1;
     }
     SHA1_Update(&ctx, tmp, len);
     free(tmp);

     if((len = str2bin(cp, &tmp)) == 0) {
	  // print error
	  return -1;
     }
     SHA1_Update(&ctx, tmp, len);
     free(tmp);

     SHA1_Final(digest, &ctx);

     return 0;
    
}