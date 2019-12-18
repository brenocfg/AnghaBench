#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  pStack; } ;
typedef  TYPE_1__ FICL_VM ;
typedef  int FICL_INT ;

/* Variables and functions */
 int FALSE ; 
 int FICL_FALSE ; 
 int FICL_TRUE ; 
 int TRUE ; 
 int isdigit (char) ; 
 int /*<<< orphan*/  ltoa (int,char*,int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int stackPopINT (int /*<<< orphan*/ ) ; 
 scalar_t__ stackPopPtr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stackPushINT (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stackPushPtr (int /*<<< orphan*/ ,char*) ; 
 int strlen (char*) ; 
 int strtol (char*,char**,int) ; 
 int /*<<< orphan*/  ultoa (int,char*,int) ; 

__attribute__((used)) static void ficlSprintf(FICL_VM *pVM) /*  */
{
	int bufferLength = stackPopINT(pVM->pStack);
	char *buffer = (char *)stackPopPtr(pVM->pStack);
	char *bufferStart = buffer;

	int formatLength = stackPopINT(pVM->pStack);
	char *format = (char *)stackPopPtr(pVM->pStack);
	char *formatStop = format + formatLength;

	int base = 10;
	int unsignedInteger = FALSE;

	FICL_INT append = FICL_TRUE;

	while (format < formatStop)
	{
		char scratch[64];
		char *source;
		int actualLength;
		int desiredLength;
		int leadingZeroes;


		if (*format != '%')
		{
			source = format;
			actualLength = desiredLength = 1;
			leadingZeroes = 0;
		}
		else
		{
			format++;
			if (format == formatStop)
				break;

			leadingZeroes = (*format == '0');
			if (leadingZeroes)
				{
				format++;
				if (format == formatStop)
					break;
				}

			desiredLength = isdigit(*format);
			if (desiredLength)
				{
				desiredLength = strtol(format, &format, 10);
				if (format == formatStop)
					break;
				}
			else if (*format == '*')
				{
				desiredLength = stackPopINT(pVM->pStack);
				format++;
				if (format == formatStop)
					break;
				}


			switch (*format)
			{
				case 's':
				case 'S':
				{
					actualLength = stackPopINT(pVM->pStack);
					source = (char *)stackPopPtr(pVM->pStack);
					break;
				}
				case 'x':
				case 'X':
					base = 16;
				case 'u':
				case 'U':
					unsignedInteger = TRUE;
				case 'd':
				case 'D':
				{
					int integer = stackPopINT(pVM->pStack);
					if (unsignedInteger)
						ultoa(integer, scratch, base);
					else
						ltoa(integer, scratch, base);
					base = 10;
					unsignedInteger = FALSE;
					source = scratch;
					actualLength = strlen(scratch);
					break;
				}
				case '%':
					source = format;
					actualLength = 1;
				default:
					continue;
			}
		}

		if (append != FICL_FALSE)
		{
			if (!desiredLength)
				desiredLength = actualLength;
			if (desiredLength > bufferLength)
			{
				append = FICL_FALSE;
				desiredLength = bufferLength;
			}
			while (desiredLength > actualLength)
				{
				*buffer++ = (char)((leadingZeroes) ? '0' : ' ');
				bufferLength--;
				desiredLength--;
				}
			memcpy(buffer, source, actualLength);
			buffer += actualLength;
			bufferLength -= actualLength;
		}

		format++;
	}

	stackPushPtr(pVM->pStack, bufferStart);
	stackPushINT(pVM->pStack, buffer - bufferStart);
	stackPushINT(pVM->pStack, append);
}