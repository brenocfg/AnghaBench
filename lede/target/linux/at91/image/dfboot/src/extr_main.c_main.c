#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;
typedef  struct TYPE_20__   TYPE_15__ ;
typedef  struct TYPE_19__   TYPE_14__ ;
typedef  struct TYPE_18__   TYPE_10__ ;

/* Type definitions */
struct TYPE_24__ {unsigned int pData; } ;
struct TYPE_23__ {int /*<<< orphan*/  (* Read ) (TYPE_3__*,char*,unsigned int volatile,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_22__ {int /*<<< orphan*/  (* Stop ) (TYPE_2__*) ;int /*<<< orphan*/  (* Start ) (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (),int /*<<< orphan*/ *) ;} ;
struct TYPE_21__ {int pages_number; int pages_size; } ;
struct TYPE_20__ {TYPE_1__ Device; int /*<<< orphan*/  id; } ;
struct TYPE_19__ {int /*<<< orphan*/  (* CRC32 ) (unsigned char const*,unsigned int volatile,unsigned int*) ;int /*<<< orphan*/  (* OpenPipe ) (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* OpenSvcXmodem ) (TYPE_4__*,int /*<<< orphan*/ ,TYPE_10__*) ;int /*<<< orphan*/  (* OpenSBuffer ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/  SYSTIMER_DESC; int /*<<< orphan*/  (* OpenCtlTempo ) (TYPE_10__*,void*) ;} ;
struct TYPE_18__ {int /*<<< orphan*/  (* CtlTempoCreate ) (TYPE_10__*,TYPE_2__*) ;int /*<<< orphan*/  (* CtlTempoStart ) (void*) ;} ;
typedef  TYPE_2__ AT91S_SvcTempo ;
typedef  int /*<<< orphan*/  AT91PS_USART ;
typedef  int /*<<< orphan*/  AT91PS_SvcComm ;
typedef  int /*<<< orphan*/  AT91PS_Buffer ;

/* Variables and functions */
 int /*<<< orphan*/  AT91C_AIC_PRIOR_HIGHEST ; 
 int /*<<< orphan*/  AT91C_AIC_SRCTYPE_INT_LEVEL_SENSITIVE ; 
 int /*<<< orphan*/  AT91C_BASE_AIC ; 
 scalar_t__ AT91C_BASE_DBGU ; 
 unsigned int AT91C_BOOT_DATAFLASH_ADDR ; 
 int /*<<< orphan*/  AT91C_DELAY_TO_BOOT ; 
 unsigned int AT91C_DOWNLOAD_BASE_ADDRESS ; 
 int volatile AT91C_DOWNLOAD_MAX_SIZE ; 
 int /*<<< orphan*/  AT91C_ID_SYS ; 
 scalar_t__ AT91C_OFFSET_VECT6 ; 
 TYPE_14__* AT91C_ROM_BOOT_ADDRESS ; 
 int /*<<< orphan*/  AT91F_AIC_ConfigureIt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AT91F_AIC_EnableIt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int AT91F_DataflashInit () ; 
 int AT91F_DisplayMenu () ; 
 int /*<<< orphan*/  AT91F_MemoryDisplay (unsigned int,int) ; 
 int /*<<< orphan*/  AT91F_ReadLine (char*,char*) ; 
 int /*<<< orphan*/  AT91F_ST_ASM_HANDLER ; 
 int /*<<< orphan*/  AT91F_SetPLL () ; 
 int /*<<< orphan*/  AT91F_StartBoot () ; 
 int /*<<< orphan*/  AT91F_WaitKeyPressed () ; 
 int /*<<< orphan*/  AsciiToHex (char*,unsigned int*) ; 
#define  CFG_DATAFLASH_LOGIC_ADDR_CS0 129 
#define  CFG_DATAFLASH_LOGIC_ADDR_CS3 128 
 scalar_t__ Program_From_MCI () ; 
 int XmodemComplete ; 
 int /*<<< orphan*/  XmodemProtocol ; 
 int /*<<< orphan*/  at91_init_uarts () ; 
 TYPE_10__ ctlTempo ; 
 TYPE_15__* dataflash_info ; 
 int /*<<< orphan*/  erase_dataflash (unsigned int) ; 
 char* message ; 
 TYPE_14__* pAT91 ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  read_dataflash (unsigned int,unsigned int volatile,char*) ; 
 int /*<<< orphan*/  sXmBuffer ; 
 int /*<<< orphan*/  stub1 (TYPE_10__*,void*) ; 
 int /*<<< orphan*/  stub10 (unsigned char const*,unsigned int volatile,unsigned int*) ; 
 int /*<<< orphan*/  stub11 (unsigned char const*,unsigned int volatile,unsigned int*) ; 
 int /*<<< orphan*/  stub2 (void*) ; 
 int /*<<< orphan*/  stub3 (TYPE_10__*,TYPE_2__*) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub5 (TYPE_4__*,int /*<<< orphan*/ ,TYPE_10__*) ; 
 int /*<<< orphan*/  stub6 (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub7 (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (),int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub8 (TYPE_2__*) ; 
 int /*<<< orphan*/  stub9 (TYPE_3__*,char*,unsigned int volatile,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__ svcXmodem ; 
 int /*<<< orphan*/  write_dataflash (unsigned int,unsigned int volatile,unsigned int volatile) ; 
 TYPE_3__ xmodemPipe ; 

int main(void)
{
#ifdef XMODEM
	AT91PS_Buffer  		pXmBuffer;
	AT91PS_SvcComm 		pSvcXmodem;
#endif
	AT91S_SvcTempo 		svcBootTempo; 	 // Link to a AT91S_Tempo object
	unsigned int		ix;
	volatile unsigned int AddressToDownload, SizeToDownload;	
 	unsigned int DeviceAddress = 0;
	char command = 0;
#ifdef XMODEM
	volatile int i = 0;	
	unsigned int crc1 = 0, crc2 = 0;
	volatile int device;
	int NbPage;
#endif
	volatile int Nb_Device = 0;
	int mci_present = 0;

	pAT91 = AT91C_ROM_BOOT_ADDRESS;

	if (!AT91F_SetPLL())
	{
		printf("F SetPLL");
		while(1);
	}

	at91_init_uarts();

	/* Tempo Initialisation */
	pAT91->OpenCtlTempo(&ctlTempo, (void *) &(pAT91->SYSTIMER_DESC));
	ctlTempo.CtlTempoStart((void *) &(pAT91->SYSTIMER_DESC));
	
	// Attach the tempo to a tempo controler
	ctlTempo.CtlTempoCreate(&ctlTempo, &svcBootTempo);
//	LED_init();
//	LED_blink(2);

#ifdef XMODEM
	/* Xmodem Initialisation */
	pXmBuffer = pAT91->OpenSBuffer(&sXmBuffer);
	pSvcXmodem = pAT91->OpenSvcXmodem(&svcXmodem,
	             (AT91PS_USART)AT91C_BASE_DBGU, &ctlTempo);
	pAT91->OpenPipe(&xmodemPipe, pSvcXmodem, pXmBuffer);
#endif

	/* System Timer initialization */
	AT91F_AIC_ConfigureIt(
		AT91C_BASE_AIC,                        // AIC base address
		AT91C_ID_SYS,                          // System peripheral ID
		AT91C_AIC_PRIOR_HIGHEST,               // Max priority
		AT91C_AIC_SRCTYPE_INT_LEVEL_SENSITIVE, // Level sensitive
		AT91F_ST_ASM_HANDLER
	);
	/* Enable ST interrupt */
	AT91F_AIC_EnableIt(AT91C_BASE_AIC, AT91C_ID_SYS);

#ifndef PRODTEST
	/* Start tempo to start Boot in a delay of
	 * AT91C_DELAY_TO_BOOT sec if no key pressed */
	svcBootTempo.Start(&svcBootTempo, AT91C_DELAY_TO_BOOT,
	                   0, AT91F_StartBoot, NULL);
#endif

	while(1)
	{
		while(command == 0)
		{
			AddressToDownload = AT91C_DOWNLOAD_BASE_ADDRESS;
			SizeToDownload = AT91C_DOWNLOAD_MAX_SIZE;
			DeviceAddress = 0;
			
			/* try to detect Dataflash */
			if (!Nb_Device)
				Nb_Device = AT91F_DataflashInit();				
							
			mci_present = AT91F_DisplayMenu();

#ifdef PRODTEST
			if (mci_present) {
				if (Program_From_MCI())
					AT91F_StartBoot();
			}
#endif

			message[0] = 0;
			AT91F_ReadLine ("Enter: ", message);

#ifndef PRODTEST
			/* stop tempo ==> stop autoboot */
			svcBootTempo.Stop(&svcBootTempo);
#endif

			command = message[0];
			for(ix = 1; (message[ix] == ' ') && (ix < 12); ix++);	// Skip some whitespace
				
			if(!AsciiToHex(&message[ix], &DeviceAddress) )
				DeviceAddress = 0;			// Illegal DeviceAddress
				
			switch(command)
			{
#ifdef XMODEM
				case '1':
				case '2':
				case '5':
					if(command == '1') {
						DeviceAddress = 0xC0000000;
//						printf("Download DataflashBoot.bin to [0x%x]\n", DeviceAddress);
					} else if(command == '2') {
						DeviceAddress = AT91C_BOOT_DATAFLASH_ADDR;
//						printf("Download u-boot.bin to [0x%x]\n", DeviceAddress);
					} else {
//						printf("Download Dataflash to [0x%x]\n", DeviceAddress);
					}
					switch(DeviceAddress & 0xFF000000)
					{
						case CFG_DATAFLASH_LOGIC_ADDR_CS0:
							if (dataflash_info[0].id == 0){
								printf("No DF");
								AT91F_WaitKeyPressed();
								command = 0;
							}

							device = 0;
						break;
					
						case CFG_DATAFLASH_LOGIC_ADDR_CS3:
							if (dataflash_info[1].id == 0){
								printf("No DF");
								AT91F_WaitKeyPressed();
								command = 0;
							}
							device = 1;
						break;
					
						default:
							command = 0;
						break;
					}
				break;
#endif

				case '3':
					if (mci_present)
						Program_From_MCI();
					command = 0;
					break;

				case '4':
					AT91F_StartBoot();
					command = 0;
				break;

#ifdef MEMDISP
				case '6':
					do 
					{
						AT91F_MemoryDisplay(DeviceAddress, 256);
						AT91F_ReadLine (NULL, message);
						DeviceAddress += 0x100;
					}
					while(message[0] == '\0');
					command = 0;
				break;
#endif

				case '7':
					switch(DeviceAddress & 0xFF000000)
					{
						case CFG_DATAFLASH_LOGIC_ADDR_CS0:
							break;
						case CFG_DATAFLASH_LOGIC_ADDR_CS3:
							break;
						default:
							command = 0;
							break;
					}

					if (command != 0) {
						AT91F_ReadLine ("RDY ERA\nSure?",
								message);
						if(message[0] == 'Y' || message[0] == 'y') {
							erase_dataflash(DeviceAddress & 0xFF000000);
//							printf("Erase complete\n\n");
						}
//						else
//							printf("Erase aborted\n");
					}
					command = 0;

				break;

				default:
					command = 0;
				break;
			}
		}
#ifdef XMODEM
		for(i = 0; i <= AT91C_DOWNLOAD_MAX_SIZE; i++)
			*(unsigned char *)(AddressToDownload + i) = 0;
	
		xmodemPipe.Read(&xmodemPipe, (char *)AddressToDownload,
		                SizeToDownload, XmodemProtocol, 0);	
		while(XmodemComplete !=1);
		SizeToDownload = (unsigned int)((svcXmodem.pData) -
		                 (unsigned int)AddressToDownload);

		/* Modification of vector 6 */
		if ((DeviceAddress == CFG_DATAFLASH_LOGIC_ADDR_CS0)) {
			// Vector 6 must be compliant to the BootRom description (ref Datasheet)
	   		NbPage = 0;
	    	i = dataflash_info[device].Device.pages_number;
	    	while(i >>= 1)
	    		NbPage++;
			i = (SizeToDownload / 512)+1 + (NbPage << 13) +
			    (dataflash_info[device].Device.pages_size << 17); //+4 to add crc32
		    SizeToDownload = 512 * (i &0xFF);
		}	
		else
		{
			/* Save the contents of vector 6 ==> will be restored 
			 * at boot time (AT91F_StartBoot) */
			*(int *)(AddressToDownload + SizeToDownload + 4) =
				*(int *)(AddressToDownload + AT91C_OFFSET_VECT6);
			/* Modify Vector 6 to contain the size of the
			 * file to copy (Dataflash -> SDRAM)*/
			i = SizeToDownload;	
		}		

		*(int *)(AddressToDownload + AT91C_OFFSET_VECT6) = i;
//		printf("\nModification of Arm Vector 6 :%x\n", i);
			    
//		printf("\nWrite %d bytes in DataFlash [0x%x]\n",SizeToDownload, DeviceAddress);
		crc1 = 0;
		pAT91->CRC32((const unsigned char *)AddressToDownload, SizeToDownload , &crc1);

		/* Add the crc32 at the end of the code */
		*(char *)(AddressToDownload + SizeToDownload)     = (char)(crc1 & 0x000000FF);
		*(char *)(AddressToDownload + SizeToDownload + 1) = (char)((crc1 & 0x0000FF00) >> 8);
		*(char *)(AddressToDownload + SizeToDownload + 2) = (char)((crc1 & 0x00FF0000) >> 16);
		*(char *)(AddressToDownload + SizeToDownload + 3) = (char)((crc1 & 0xFF000000) >> 24);

		/* write dataflash */
		write_dataflash (DeviceAddress, AddressToDownload, (SizeToDownload + 8));

		/* clear the buffer before read */
		for(i=0; i <= SizeToDownload; i++)
			*(unsigned char *)(AddressToDownload + i) = 0;
					
		/* Read dataflash to check the validity of the data */
		read_dataflash (DeviceAddress, (SizeToDownload + 4), (char *)(AddressToDownload));

		printf("VFY: ");	
		crc2 = 0;
				
		pAT91->CRC32((const unsigned char *)AddressToDownload, SizeToDownload , &crc2);
 		crc1 = (int)(*(char *)(AddressToDownload + SizeToDownload))          +
			   (int)(*(char *)(AddressToDownload + SizeToDownload + 1) << 8) +
			   (int)(*(char *)(AddressToDownload + SizeToDownload + 2) << 16) +
			   (int)(*(char *)(AddressToDownload + SizeToDownload + 3) << 24);

		if (crc1 != crc2)
		 	printf("ERR");
		else
		 	printf("OK");
		 	
 		command = 0;
 		XmodemComplete = 0;
		AT91F_WaitKeyPressed();
#endif
 	}
}