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
struct hex_options {scalar_t__ decode_flag; } ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ fread (char*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 size_t fwrite (char*,int,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ hex_decode (char*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ hex_encode (char*,scalar_t__,char**) ; 
 scalar_t__ isspace (unsigned char) ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  stdout ; 
 size_t strcspn (char*,char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 

int
hxtool_hex(struct hex_options *opt, int argc, char **argv)
{

    if (opt->decode_flag) {
	char buf[1024], buf2[1024], *p;
	ssize_t len;

	while(fgets(buf, sizeof(buf), stdin) != NULL) {
	    buf[strcspn(buf, "\r\n")] = '\0';
	    p = buf;
	    while(isspace(*(unsigned char *)p))
		p++;
	    len = hex_decode(p, buf2, strlen(p));
	    if (len < 0)
		errx(1, "hex_decode failed");
	    if (fwrite(buf2, 1, len, stdout) != (size_t)len)
		errx(1, "fwrite failed");
	}
    } else {
        char buf[28], *p;
	ssize_t len;

	while((len = fread(buf, 1, sizeof(buf), stdin)) != 0) {
	    len = hex_encode(buf, len, &p);
	    if (len < 0)
	        continue;
	    fprintf(stdout, "%s\n", p);
	    free(p);
	}
    }
    return 0;
}