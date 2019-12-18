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
typedef  int /*<<< orphan*/  u_int32_t ;
typedef  int u_int ;
typedef  scalar_t__ u_char ;
struct sockaddr_ng {scalar_t__ sg_len; int /*<<< orphan*/  sg_data; int /*<<< orphan*/  sg_family; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  sagbuf ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  AF_NETGRAPH ; 
 int BUF_SIZE ; 
 int CMDRTN_ERROR ; 
 int CMDRTN_OK ; 
 int CMDRTN_USAGE ; 
 int /*<<< orphan*/  dsock ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int fread (scalar_t__*,int,int,int /*<<< orphan*/ *) ; 
 int sendto (int /*<<< orphan*/ ,scalar_t__*,int,int /*<<< orphan*/ ,struct sockaddr*,scalar_t__) ; 
 int sscanf (char*,char*,int*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/  warn (char*,char const*) ; 
 int /*<<< orphan*/  warnx (char*,char*) ; 

__attribute__((used)) static int
WriteCmd(int ac, char **av)
{
	u_int32_t sagbuf[64];
	struct sockaddr_ng *sag = (struct sockaddr_ng *)sagbuf;
	u_char buf[BUF_SIZE];
	const char *hook;
	FILE *fp;
	u_int len;
	int byte;
	int i;

	/* Get arguments */
	if (ac < 3)
		return (CMDRTN_USAGE);
	hook = av[1];

	/* Get data */
	if (strcmp(av[2], "-f") == 0) {
		if (ac != 4)
			return (CMDRTN_USAGE);
		if ((fp = fopen(av[3], "r")) == NULL) {
			warn("can't read file \"%s\"", av[3]);
			return (CMDRTN_ERROR);
		}
		if ((len = fread(buf, 1, sizeof(buf), fp)) == 0) {
			if (ferror(fp))
				warn("can't read file \"%s\"", av[3]);
			else
				warnx("file \"%s\" is empty", av[3]);
			fclose(fp);
			return (CMDRTN_ERROR);
		}
		fclose(fp);
	} else {
		for (i = 2, len = 0; i < ac && len < sizeof(buf); i++, len++) {
			if (sscanf(av[i], "%i", &byte) != 1
			    || (byte < -128 || byte > 255)) {
				warnx("invalid byte \"%s\"", av[i]);
				return (CMDRTN_ERROR);
			}
			buf[len] = (u_char)byte;
		}
		if (len == 0)
			return (CMDRTN_USAGE);
	}

	/* Send data */
	sag->sg_len = 3 + strlen(hook);
	sag->sg_family = AF_NETGRAPH;
	strlcpy(sag->sg_data, hook, sizeof(sagbuf) - 2);
	if (sendto(dsock, buf, len,
	    0, (struct sockaddr *)sag, sag->sg_len) == -1) {
		warn("writing to hook \"%s\"", hook);
		return (CMDRTN_ERROR);
	}

	/* Done */
	return (CMDRTN_OK);
}