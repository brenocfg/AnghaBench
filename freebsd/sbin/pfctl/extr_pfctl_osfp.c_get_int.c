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
 int T_DC ; 
 int T_MOD ; 
 int T_MSS ; 
 int T_MTU ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,int,...) ; 
 char* get_field (char**,size_t*,int*) ; 
 int /*<<< orphan*/  stderr ; 

int
get_int(char **line, size_t *len, int *var, int *mod,
    const char *name, int flags, int max, const char *filename, int lineno)
{
	int fieldlen, i;
	char *field;
	long val = 0;

	if (mod)
		*mod = 0;
	*var = 0;

	field = get_field(line, len, &fieldlen);
	if (field == NULL)
		return (1);
	if (fieldlen == 0) {
		fprintf(stderr, "%s:%d empty %s\n", filename, lineno, name);
		return (1);
	}

	i = 0;
	if ((*field == '%' || *field == 'S' || *field == 'T' || *field == '*')
	    && fieldlen >= 1) {
		switch (*field) {
		case 'S':
			if (mod && (flags & T_MSS))
				*mod = T_MSS;
			if (fieldlen == 1)
				return (0);
			break;
		case 'T':
			if (mod && (flags & T_MTU))
				*mod = T_MTU;
			if (fieldlen == 1)
				return (0);
			break;
		case '*':
			if (fieldlen != 1) {
				fprintf(stderr, "%s:%d long '%c' %s\n",
				    filename, lineno, *field, name);
				return (1);
			}
			if (mod && (flags & T_DC)) {
				*mod = T_DC;
				return (0);
			}
		case '%':
			if (mod && (flags & T_MOD))
				*mod = T_MOD;
			if (fieldlen == 1) {
				fprintf(stderr, "%s:%d modulus %s must have a "
				    "value\n", filename, lineno, name);
				return (1);
			}
			break;
		}
		if (mod == NULL || *mod == 0) {
			fprintf(stderr, "%s:%d does not allow %c' %s\n",
			    filename, lineno, *field, name);
			return (1);
		}
		i++;
	}

	for (; i < fieldlen; i++) {
		if (field[i] < '0' || field[i] > '9') {
			fprintf(stderr, "%s:%d non-digit character in %s\n",
			    filename, lineno, name);
			return (1);
		}
		val = val * 10 + field[i] - '0';
		if (val < 0) {
			fprintf(stderr, "%s:%d %s overflowed\n", filename,
			    lineno, name);
			return (1);
		}
	}

	if (val > max) {
		fprintf(stderr, "%s:%d %s value %ld > %d\n", filename, lineno,
		    name, val, max);
		return (1);
	}
	*var = (int)val;

	return (0);
}