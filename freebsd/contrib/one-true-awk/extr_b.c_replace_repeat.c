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
typedef  char uschar ;

/* Variables and functions */
 int /*<<< orphan*/  FATAL (char*,int /*<<< orphan*/ ) ; 
 int REPEAT_PLUS_APPENDED ; 
 int REPEAT_WITH_Q ; 
 int REPEAT_ZERO ; 
 char const* basestr ; 
 char const* firstbasestr ; 
 int /*<<< orphan*/  lastre ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 char* prestr ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  xfree (char const*) ; 

__attribute__((used)) static int
replace_repeat(const uschar *reptok, int reptoklen, const uschar *atom,
	       int atomlen, int firstnum, int secondnum, int special_case)
{
	int i, j;
	uschar *buf = 0;
	int ret = 1;
	int init_q = (firstnum==0);		/* first added char will be ? */
	int n_q_reps = secondnum-firstnum;	/* m>n, so reduce until {1,m-n} left  */
	int prefix_length = reptok - basestr;	/* prefix includes first rep	*/
	int suffix_length = strlen((char *) reptok) - reptoklen;	/* string after rep specifier	*/
	int size = prefix_length +  suffix_length;

	if (firstnum > 1) {	/* add room for reps 2 through firstnum */
		size += atomlen*(firstnum-1);
	}

	/* Adjust size of buffer for special cases */
	if (special_case == REPEAT_PLUS_APPENDED) {
		size++;		/* for the final + */
	} else if (special_case == REPEAT_WITH_Q) {
		size += init_q + (atomlen+1)* n_q_reps;
	} else if (special_case == REPEAT_ZERO) {
		size += 2;	/* just a null ERE: () */
	}
	if ((buf = (uschar *) malloc(size+1)) == NULL)
		FATAL("out of space in reg expr %.10s..", lastre);
	memcpy(buf, basestr, prefix_length);	/* copy prefix	*/
	j = prefix_length;
	if (special_case == REPEAT_ZERO) {
		j -= atomlen;
		buf[j++] = '(';
		buf[j++] = ')';
	}
	for (i=1; i < firstnum; i++) {		/* copy x reps 	*/
		memcpy(&buf[j], atom, atomlen);
		j += atomlen;
	}
	if (special_case == REPEAT_PLUS_APPENDED) {
		buf[j++] = '+';
	} else if (special_case == REPEAT_WITH_Q) {
		if (init_q) buf[j++] = '?';
		for (i=0; i < n_q_reps; i++) {	/* copy x? reps */
			memcpy(&buf[j], atom, atomlen);
			j += atomlen;
			buf[j++] = '?';
		}
	}
	memcpy(&buf[j], reptok+reptoklen, suffix_length);
	if (special_case == REPEAT_ZERO) {
		buf[j+suffix_length] = '\0';
	} else {
		buf[size] = '\0';
	}
	/* free old basestr */
	if (firstbasestr != basestr) {
		if (basestr)
			xfree(basestr);
	}
	basestr = buf;
	prestr  = buf + prefix_length;
	if (special_case == REPEAT_ZERO) {
		prestr  -= atomlen;
		ret++;
	}
	return ret;
}