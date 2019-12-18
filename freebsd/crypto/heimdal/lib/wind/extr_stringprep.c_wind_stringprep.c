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
typedef  int wind_profile_flags ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  out ;

/* Variables and functions */
 int ENOMEM ; 
 int WIND_PROFILE_LDAP_CASE_EXACT_ASSERTION ; 
 int WIND_PROFILE_LDAP_CASE_EXACT_ATTRIBUTE ; 
 int WIND_PROFILE_LDAP_NUMERIC ; 
 int WIND_PROFILE_LDAP_TELEPHONE ; 
 int _wind_ldap_case_exact_attribute (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *,size_t*) ; 
 int _wind_stringprep_map (int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ *,size_t*,int) ; 
 int _wind_stringprep_normalize (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *,size_t*) ; 
 int _wind_stringprep_prohibited (int /*<<< orphan*/ *,size_t,int) ; 
 int _wind_stringprep_testbidi (int /*<<< orphan*/ *,size_t,int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

int
wind_stringprep(const uint32_t *in, size_t in_len,
		uint32_t *out, size_t *out_len,
		wind_profile_flags flags)
{
    size_t tmp_len = in_len * 3;
    uint32_t *tmp;
    int ret;
    size_t olen;

    if (in_len == 0) {
	*out_len = 0;
	return 0;
    }

    tmp = malloc(tmp_len * sizeof(uint32_t));
    if (tmp == NULL)
	return ENOMEM;

    ret = _wind_stringprep_map(in, in_len, tmp, &tmp_len, flags);
    if (ret) {
	free(tmp);
	return ret;
    }

    olen = *out_len;
    ret = _wind_stringprep_normalize(tmp, tmp_len, tmp, &olen);
    if (ret) {
	free(tmp);
	return ret;
    }
    ret = _wind_stringprep_prohibited(tmp, olen, flags);
    if (ret) {
	free(tmp);
	return ret;
    }
    ret = _wind_stringprep_testbidi(tmp, olen, flags);
    if (ret) {
	free(tmp);
	return ret;
    }

    /* Insignificant Character Handling for ldap-prep */
    if (flags & WIND_PROFILE_LDAP_CASE_EXACT_ATTRIBUTE) {
	ret = _wind_ldap_case_exact_attribute(tmp, olen, out, out_len);
#if 0
    } else if (flags & WIND_PROFILE_LDAP_CASE_EXACT_ASSERTION) {
    } else if (flags & WIND_PROFILE_LDAP_NUMERIC) {
    } else if (flags & WIND_PROFILE_LDAP_TELEPHONE) {
#endif
    } else {
	memcpy(out, tmp, sizeof(out[0]) * olen);
	*out_len = olen;
    }
    free(tmp);

    return ret;
}