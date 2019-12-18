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
 int MBO_ALL_TYPE ; 
 int MBO_TYPE_BLK ; 
 int MBO_TYPE_CHR ; 
 int MBO_TYPE_DIR ; 
 int MBO_TYPE_FIFO ; 
 int MBO_TYPE_LNK ; 
 int MBO_TYPE_REG ; 
 int MBO_TYPE_SOCK ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,char) ; 
 int strlen (char*) ; 

__attribute__((used)) static int
bsde_parse_type(char *spec, int *type, size_t buflen, char *errstr)
{
	int i;

	*type = 0;
	for (i = 0; i < strlen(spec); i++) {
		switch (spec[i]) {
		case 'r':
		case '-':
			*type |= MBO_TYPE_REG;
			break;
		case 'd':
			*type |= MBO_TYPE_DIR;
			break;
		case 'b':
			*type |= MBO_TYPE_BLK;
			break;
		case 'c':
			*type |= MBO_TYPE_CHR;
			break;
		case 'l':
			*type |= MBO_TYPE_LNK;
			break;
		case 's':
			*type |= MBO_TYPE_SOCK;
			break;
		case 'p':
			*type |= MBO_TYPE_FIFO;
			break;
		case 'a':
			*type |= MBO_ALL_TYPE;
			break;
		default:
			snprintf(errstr, buflen, "Unknown type code: %c",
			    spec[i]);
			return (-1);
		}
	}

	return (0);
}