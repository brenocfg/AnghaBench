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
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 long BIO_get_mem_data (int /*<<< orphan*/ *,char**) ; 
 int /*<<< orphan*/  BIO_seek (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (char*,char*,size_t) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 scalar_t__ strncasecmp (char*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
xml_is_zone_name(BIO* zone, const char* name)
{
	char buf[1024];
	char* z = NULL;
	long zlen;
	(void)BIO_seek(zone, 0);
	zlen = BIO_get_mem_data(zone, &z);
	if(!zlen || !z) return 0;
	/* zero terminate */
	if(zlen >= (long)sizeof(buf)) return 0;
	memmove(buf, z, (size_t)zlen);
	buf[zlen] = 0;
	/* compare */
	return (strncasecmp(buf, name, strlen(name)) == 0);
}