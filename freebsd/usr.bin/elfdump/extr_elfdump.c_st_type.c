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
typedef  int /*<<< orphan*/  s_type ;

/* Variables and functions */
 unsigned int EM_SPARCV9 ; 
#define  STT_COMMON 134 
#define  STT_FILE 133 
#define  STT_FUNC 132 
#define  STT_NOTYPE 131 
#define  STT_OBJECT 130 
#define  STT_SECTION 129 
#define  STT_TLS 128 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned int) ; 

__attribute__((used)) static const char *
st_type(unsigned int mach, unsigned int type)
{
        static char s_type[32];

        switch (type) {
        case STT_NOTYPE: return "STT_NOTYPE";
        case STT_OBJECT: return "STT_OBJECT";
        case STT_FUNC: return "STT_FUNC";
        case STT_SECTION: return "STT_SECTION";
        case STT_FILE: return "STT_FILE";
        case STT_COMMON: return "STT_COMMON";
        case STT_TLS: return "STT_TLS";
        case 13:
                if (mach == EM_SPARCV9)
                        return "STT_SPARC_REGISTER";
                break;
        }
        snprintf(s_type, sizeof(s_type), "<unknown: %#x>", type);
        return (s_type);
}