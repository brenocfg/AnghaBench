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
typedef  size_t u8 ;
typedef  int u32 ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  cha_err_code ;

/* Variables and functions */
 size_t ARRAY_SIZE (char**) ; 
 int EBADMSG ; 
 int EINVAL ; 
 int const JRSTA_CCBERR_CHAID_MASK ; 
 size_t JRSTA_CCBERR_CHAID_RNG ; 
 int const JRSTA_CCBERR_CHAID_SHIFT ; 
 size_t JRSTA_CCBERR_ERRID_ICVCHK ; 
 int const JRSTA_CCBERR_ERRID_MASK ; 
 int const JRSTA_DECOERR_INDEX_MASK ; 
 int const JRSTA_DECOERR_INDEX_SHIFT ; 
 int const JRSTA_DECOERR_JUMP ; 
 char** cha_id_list ; 
 int /*<<< orphan*/  dev_err_ratelimited (struct device*,char*,int const,char const*,char*,size_t,char const*,char*,char const*,char*) ; 
 char** err_id_list ; 
 char** rng_err_id_list ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,size_t) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static int report_ccb_status(struct device *jrdev, const u32 status,
			     const char *error)
{
	u8 cha_id = (status & JRSTA_CCBERR_CHAID_MASK) >>
		    JRSTA_CCBERR_CHAID_SHIFT;
	u8 err_id = status & JRSTA_CCBERR_ERRID_MASK;
	u8 idx = (status & JRSTA_DECOERR_INDEX_MASK) >>
		  JRSTA_DECOERR_INDEX_SHIFT;
	char *idx_str;
	const char *cha_str = "unidentified cha_id value 0x";
	char cha_err_code[3] = { 0 };
	const char *err_str = "unidentified err_id value 0x";
	char err_err_code[3] = { 0 };

	if (status & JRSTA_DECOERR_JUMP)
		idx_str = "jump tgt desc idx";
	else
		idx_str = "desc idx";

	if (cha_id < ARRAY_SIZE(cha_id_list))
		cha_str = cha_id_list[cha_id];
	else
		snprintf(cha_err_code, sizeof(cha_err_code), "%02x", cha_id);

	if ((cha_id << JRSTA_CCBERR_CHAID_SHIFT) == JRSTA_CCBERR_CHAID_RNG &&
	    err_id < ARRAY_SIZE(rng_err_id_list) &&
	    strlen(rng_err_id_list[err_id])) {
		/* RNG-only error */
		err_str = rng_err_id_list[err_id];
	} else {
		err_str = err_id_list[err_id];
	}

	/*
	 * CCB ICV check failures are part of normal operation life;
	 * we leave the upper layers to do what they want with them.
	 */
	if (err_id == JRSTA_CCBERR_ERRID_ICVCHK)
		return -EBADMSG;

	dev_err_ratelimited(jrdev, "%08x: %s: %s %d: %s%s: %s%s\n", status,
			    error, idx_str, idx, cha_str, cha_err_code,
			    err_str, err_err_code);

	return -EINVAL;
}