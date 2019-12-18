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
typedef  char u_char ;
typedef  enum filetype { ____Placeholder_filetype } filetype ;

/* Variables and functions */
 int /*<<< orphan*/  BZIP2_MAGIC ; 
 int FT_BZIP2 ; 
 int FT_GZIP ; 
 int FT_LZ ; 
 int FT_PACK ; 
 int FT_UNKNOWN ; 
 int FT_XZ ; 
 int FT_Z ; 
 char GZIP_MAGIC0 ; 
 char GZIP_MAGIC1 ; 
 char GZIP_OMAGIC1 ; 
 int /*<<< orphan*/  LZ_MAGIC ; 
 int /*<<< orphan*/  PACK_MAGIC ; 
 int /*<<< orphan*/  XZ_MAGIC ; 
 int /*<<< orphan*/  Z_MAGIC ; 
 scalar_t__ memcmp (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static enum filetype
file_gettype(u_char *buf)
{

	if (buf[0] == GZIP_MAGIC0 &&
	    (buf[1] == GZIP_MAGIC1 || buf[1] == GZIP_OMAGIC1))
		return FT_GZIP;
	else
#ifndef NO_BZIP2_SUPPORT
	if (memcmp(buf, BZIP2_MAGIC, 3) == 0 &&
	    buf[3] >= '0' && buf[3] <= '9')
		return FT_BZIP2;
	else
#endif
#ifndef NO_COMPRESS_SUPPORT
	if (memcmp(buf, Z_MAGIC, 2) == 0)
		return FT_Z;
	else
#endif
#ifndef NO_PACK_SUPPORT
	if (memcmp(buf, PACK_MAGIC, 2) == 0)
		return FT_PACK;
	else
#endif
#ifndef NO_XZ_SUPPORT
	if (memcmp(buf, XZ_MAGIC, 4) == 0)	/* XXX: We only have 4 bytes */
		return FT_XZ;
	else
#endif
#ifndef NO_LZ_SUPPORT
	if (memcmp(buf, LZ_MAGIC, 4) == 0)
		return FT_LZ;
	else
#endif
		return FT_UNKNOWN;
}