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
typedef  int /*<<< orphan*/  UWORD ;
typedef  size_t UBYTE ;

/* Variables and functions */
 int /*<<< orphan*/  C1 ; 
 int /*<<< orphan*/  C2 ; 
 int /*<<< orphan*/  C3 ; 
 int /*<<< orphan*/  C4 ; 
 int /*<<< orphan*/  NR13_REG ; 
 int /*<<< orphan*/  NR23_REG ; 
 int NR24_REG ; 
 int NR51_REG ; 
 int /*<<< orphan*/  R1 ; 
 int /*<<< orphan*/  R2 ; 
 int /*<<< orphan*/  R3 ; 
 int /*<<< orphan*/  R4 ; 
 int /*<<< orphan*/  delay (int /*<<< orphan*/ ) ; 

void dialtone(UWORD dtmf_on, UWORD dtmf_off, char str[20])
{
	UBYTE i = 0;
	
	while(str[i]){
		switch(str[i]){
		    case '1':
			  NR13_REG = R1;
			  NR23_REG = C1; 
			  break;
		    case '2':
			  NR13_REG = R1;
			  NR23_REG = C2;
			  break;
		    case '3':
			  NR13_REG = R1;
			  NR23_REG = C3;	
			  break;
		    case 'A':
		    case 'a':
			  NR13_REG = R1;
			  NR23_REG = C4;  
			  break;
		    case '4':
			  NR13_REG = R2;
			  NR23_REG = C1;	
			  break;
		    case '5':
			  NR13_REG = R2;
			  NR23_REG = C2;	
			  break;
		    case '6':
			  NR13_REG = R2;
			  NR23_REG = C3;	
			  break;
			case 'B':
			case 'b':
			  NR13_REG = R2;
			  NR23_REG = C4;	
			  break;
			case '7':
			  NR13_REG = R3;
			  NR23_REG = C1;	
			  break;
			case '8':
			  NR13_REG = R3;
			  NR23_REG = C2;	
			  break;
			case '9':
			  NR13_REG = R3;
			  NR23_REG = C3;	
			  break;
			case 'C':
			case 'c':
			  NR13_REG = R3;
			  NR23_REG = C4;	
			  break;
			case '*':
			  NR13_REG = R4;
			  NR23_REG = C1;	
			  break;
			case '0':
			  NR13_REG = R4;
			  NR23_REG = C2;	
			  break;
			case '#':
			  NR13_REG = R4;
			  NR23_REG = C3;	
			  break;
			case 'D':
			case 'd':
			  NR13_REG = R4;
			  NR23_REG = C4;	
			  break;
			case ',':
			  delay(dtmf_on);	/* keep on */
			  delay(dtmf_off);	/* keep off */
			 
			default:
			  NR51_REG = 0x00U;	/* sound off */
			  goto skip;
			  
		  }
		NR24_REG = 0x87U;	/* ch2 tips */
		NR51_REG = 0x33U;	/* sound on */
		delay(dtmf_on);		/* keep on */

		NR51_REG = 0x00U;	/* sound off */
		delay(dtmf_off);	/* keep off */

	  skip:
		i++;
	}
}