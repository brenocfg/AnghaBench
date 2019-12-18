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
struct varobj {int format; } ;
typedef  enum varobj_display_formats { ____Placeholder_varobj_display_formats } varobj_display_formats ;

/* Variables and functions */
#define  FORMAT_BINARY 132 
#define  FORMAT_DECIMAL 131 
#define  FORMAT_HEXADECIMAL 130 
#define  FORMAT_NATURAL 129 
#define  FORMAT_OCTAL 128 
 int variable_default_display (struct varobj*) ; 

enum varobj_display_formats
varobj_set_display_format (struct varobj *var,
			   enum varobj_display_formats format)
{
  switch (format)
    {
    case FORMAT_NATURAL:
    case FORMAT_BINARY:
    case FORMAT_DECIMAL:
    case FORMAT_HEXADECIMAL:
    case FORMAT_OCTAL:
      var->format = format;
      break;

    default:
      var->format = variable_default_display (var);
    }

  return var->format;
}