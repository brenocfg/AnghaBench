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
typedef  int /*<<< orphan*/  ulongval ;
typedef  int /*<<< orphan*/  uintval ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int u_int ;
typedef  int /*<<< orphan*/  u8val ;
typedef  int /*<<< orphan*/  u64val ;
typedef  int /*<<< orphan*/  u32val ;
typedef  int /*<<< orphan*/  u16val ;
typedef  int /*<<< orphan*/  longval ;
typedef  int /*<<< orphan*/  intval ;
typedef  int /*<<< orphan*/  int8_t ;
typedef  int /*<<< orphan*/  int64_t ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  int16_t ;
typedef  int /*<<< orphan*/  i8val ;
typedef  int /*<<< orphan*/  i64val ;
typedef  int /*<<< orphan*/  i32val ;
typedef  int /*<<< orphan*/  i16val ;

/* Variables and functions */
 int CTLTYPE ; 
#define  CTLTYPE_INT 139 
#define  CTLTYPE_LONG 138 
#define  CTLTYPE_S16 137 
#define  CTLTYPE_S32 136 
#define  CTLTYPE_S64 135 
#define  CTLTYPE_S8 134 
#define  CTLTYPE_U16 133 
#define  CTLTYPE_U32 132 
#define  CTLTYPE_U64 131 
#define  CTLTYPE_U8 130 
#define  CTLTYPE_UINT 129 
#define  CTLTYPE_ULONG 128 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  memcpy (char*,void const*,size_t) ; 
 void* realloc (void*,size_t) ; 
 int strIKtoi (char const*,char**,char const*) ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 
 int /*<<< orphan*/  strtoimax (char const*,char**,int /*<<< orphan*/ ) ; 
 long strtol (char const*,char**,int /*<<< orphan*/ ) ; 
 unsigned long strtoul (char const*,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strtoumax (char const*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
parse_numeric(const char *newvalstr, const char *fmt, u_int kind,
    void **newbufp, size_t *newsizep)
{
	void *newbuf;
	const void *newval;
	int8_t i8val;
	uint8_t u8val;
	int16_t i16val;
	uint16_t u16val;
	int32_t i32val;
	uint32_t u32val;
	int intval;
	unsigned int uintval;
	long longval;
	unsigned long ulongval;
	int64_t i64val;
	uint64_t u64val;
	size_t valsize;
	char *endptr = NULL;
	
	errno = 0;

	switch (kind & CTLTYPE) {
	case CTLTYPE_INT:
		if (strncmp(fmt, "IK", 2) == 0)
			intval = strIKtoi(newvalstr, &endptr, fmt);
		else
			intval = (int)strtol(newvalstr, &endptr, 0);
		newval = &intval;
		valsize = sizeof(intval);
		break;
	case CTLTYPE_UINT:
		uintval = (int) strtoul(newvalstr, &endptr, 0);
		newval = &uintval;
		valsize = sizeof(uintval);
		break;
	case CTLTYPE_LONG:
		longval = strtol(newvalstr, &endptr, 0);
		newval = &longval;
		valsize = sizeof(longval);
		break;
	case CTLTYPE_ULONG:
		ulongval = strtoul(newvalstr, &endptr, 0);
		newval = &ulongval;
		valsize = sizeof(ulongval);
		break;
	case CTLTYPE_S8:
		i8val = (int8_t)strtol(newvalstr, &endptr, 0);
		newval = &i8val;
		valsize = sizeof(i8val);
		break;
	case CTLTYPE_S16:
		i16val = (int16_t)strtol(newvalstr, &endptr, 0);
		newval = &i16val;
		valsize = sizeof(i16val);
		break;
	case CTLTYPE_S32:
		i32val = (int32_t)strtol(newvalstr, &endptr, 0);
		newval = &i32val;
		valsize = sizeof(i32val);
		break;
	case CTLTYPE_S64:
		i64val = strtoimax(newvalstr, &endptr, 0);
		newval = &i64val;
		valsize = sizeof(i64val);
		break;
	case CTLTYPE_U8:
		u8val = (uint8_t)strtoul(newvalstr, &endptr, 0);
		newval = &u8val;
		valsize = sizeof(u8val);
		break;
	case CTLTYPE_U16:
		u16val = (uint16_t)strtoul(newvalstr, &endptr, 0);
		newval = &u16val;
		valsize = sizeof(u16val);
		break;
	case CTLTYPE_U32:
		u32val = (uint32_t)strtoul(newvalstr, &endptr, 0);
		newval = &u32val;
		valsize = sizeof(u32val);
		break;
	case CTLTYPE_U64:
		u64val = strtoumax(newvalstr, &endptr, 0);
		newval = &u64val;
		valsize = sizeof(u64val);
		break;
	default:
		/* NOTREACHED */
		abort();
	}
	
	if (errno != 0 || endptr == newvalstr ||
	    (endptr != NULL && *endptr != '\0'))
		return (false);

	newbuf = realloc(*newbufp, *newsizep + valsize);
	if (newbuf == NULL)
		err(1, "out of memory");
	memcpy((char *)newbuf + *newsizep, newval, valsize);
	*newbufp = newbuf;
	*newsizep += valsize;
	
	return (true);
}