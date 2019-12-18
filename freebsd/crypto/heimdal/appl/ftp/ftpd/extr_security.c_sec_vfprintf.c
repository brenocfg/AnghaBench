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
typedef  int /*<<< orphan*/  va_list ;
struct TYPE_2__ {int (* encode ) (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__,void**) ;} ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  app_data ; 
 scalar_t__ base64_encode (void*,int,char**) ; 
 scalar_t__ command_prot ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 TYPE_1__* mech ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ prot_confidential ; 
 scalar_t__ prot_private ; 
 scalar_t__ prot_safe ; 
 int /*<<< orphan*/  sec_complete ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int stub1 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__,void**) ; 
 int vasprintf (char**,char const*,int /*<<< orphan*/ ) ; 
 int vfprintf (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 

int
sec_vfprintf(FILE *f, const char *fmt, va_list ap)
{
    char *buf;
    void *enc;
    int len;
    if(!sec_complete)
	return vfprintf(f, fmt, ap);

    if (vasprintf(&buf, fmt, ap) == -1) {
	printf("Failed to allocate command.\n");
	return -1;
    }
    len = (*mech->encode)(app_data, buf, strlen(buf), command_prot, &enc);
    free(buf);
    if(len < 0) {
	printf("Failed to encode command.\n");
	return -1;
    }
    if(base64_encode(enc, len, &buf) < 0){
	free(enc);
	printf("Out of memory base64-encoding.\n");
	return -1;
    }
    free(enc);
#ifdef FTP_SERVER
    if(command_prot == prot_safe)
	fprintf(f, "631 %s\r\n", buf);
    else if(command_prot == prot_private)
	fprintf(f, "632 %s\r\n", buf);
    else if(command_prot == prot_confidential)
	fprintf(f, "633 %s\r\n", buf);
#else
    if(command_prot == prot_safe)
	fprintf(f, "MIC %s", buf);
    else if(command_prot == prot_private)
	fprintf(f, "ENC %s", buf);
    else if(command_prot == prot_confidential)
	fprintf(f, "CONF %s", buf);
#endif
    free(buf);
    return 0;
}