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
typedef  int UInt32 ;
typedef  int Byte ;

/* Variables and functions */
 int /*<<< orphan*/  AesCbc_Decode ; 
 int /*<<< orphan*/  AesCbc_Decode_Intel ; 
 int /*<<< orphan*/  AesCbc_Encode ; 
 int /*<<< orphan*/  AesCbc_Encode_Intel ; 
 int /*<<< orphan*/  AesCtr_Code ; 
 int /*<<< orphan*/  AesCtr_Code_Intel ; 
 scalar_t__ CPU_Is_Aes_Supported () ; 
 void** DD (int) ; 
 int* InvS ; 
 size_t* Sbox ; 
 void** TT (int) ; 
 void* Ui32 (int,int,int,int) ; 
 int /*<<< orphan*/  g_AesCbc_Decode ; 
 int /*<<< orphan*/  g_AesCbc_Encode ; 
 int /*<<< orphan*/  g_AesCtr_Code ; 
 int xtime (int) ; 

void AesGenTables(void)
{
  unsigned i;
  for (i = 0; i < 256; i++)
    InvS[Sbox[i]] = (Byte)i;
  
  for (i = 0; i < 256; i++)
  {
    {
      UInt32 a1 = Sbox[i];
      UInt32 a2 = xtime(a1);
      UInt32 a3 = a2 ^ a1;
      TT(0)[i] = Ui32(a2, a1, a1, a3);
      TT(1)[i] = Ui32(a3, a2, a1, a1);
      TT(2)[i] = Ui32(a1, a3, a2, a1);
      TT(3)[i] = Ui32(a1, a1, a3, a2);
    }
    {
      UInt32 a1 = InvS[i];
      UInt32 a2 = xtime(a1);
      UInt32 a4 = xtime(a2);
      UInt32 a8 = xtime(a4);
      UInt32 a9 = a8 ^ a1;
      UInt32 aB = a8 ^ a2 ^ a1;
      UInt32 aD = a8 ^ a4 ^ a1;
      UInt32 aE = a8 ^ a4 ^ a2;
      DD(0)[i] = Ui32(aE, a9, aD, aB);
      DD(1)[i] = Ui32(aB, aE, a9, aD);
      DD(2)[i] = Ui32(aD, aB, aE, a9);
      DD(3)[i] = Ui32(a9, aD, aB, aE);
    }
  }
  
  g_AesCbc_Encode = AesCbc_Encode;
  g_AesCbc_Decode = AesCbc_Decode;
  g_AesCtr_Code = AesCtr_Code;
  
  #ifdef MY_CPU_X86_OR_AMD64
  if (CPU_Is_Aes_Supported())
  {
    g_AesCbc_Encode = AesCbc_Encode_Intel;
    g_AesCbc_Decode = AesCbc_Decode_Intel;
    g_AesCtr_Code = AesCtr_Code_Intel;
  }
  #endif
}