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
 int FALSE ; 
 int /*<<< orphan*/  TR (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TRACE_DATABASE ; 
 int /*<<< orphan*/  _nc_visbuf2 (int,char*) ; 
 int is_csi (char*) ; 
 char* skip_zero (char*) ; 
 size_t strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,size_t) ; 

__attribute__((used)) static bool
similar_sgr(char *a, char *b)
{
    bool result = FALSE;
    if (a != 0 && b != 0) {
	int csi_a = is_csi(a);
	int csi_b = is_csi(b);
	size_t len_a;
	size_t len_b;

	TR(TRACE_DATABASE, ("similar_sgr:\n\t%s\n\t%s",
			    _nc_visbuf2(1, a),
			    _nc_visbuf2(2, b)));
	if (csi_a != 0 && csi_b != 0 && csi_a == csi_b) {
	    a += csi_a;
	    b += csi_b;
	    if (*a != *b) {
		a = skip_zero(a);
		b = skip_zero(b);
	    }
	}
	len_a = strlen(a);
	len_b = strlen(b);
	if (len_a && len_b) {
	    if (len_a > len_b)
		result = (strncmp(a, b, len_b) == 0);
	    else
		result = (strncmp(a, b, len_a) == 0);
	}
	TR(TRACE_DATABASE, ("...similar_sgr: %d\n\t%s\n\t%s", result,
			    _nc_visbuf2(1, a),
			    _nc_visbuf2(2, b)));
    }
    return result;
}